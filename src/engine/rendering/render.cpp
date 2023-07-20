#include "render.hpp"

bool Renderer::initRenderer(SDL_Rect* windowRect){
    this->windowRectangle = windowRect;
    if(this->windowRectangle==nullptr){
        logErr("renderObject windowRectangle is nullptr");
        return false;
    }

    return true;
}

bool Renderer::basicRenderTexture(Texture txt){
    SDL_RenderCopy(global.renderer, txt.textureTexture, txt.textureRectangle, windowRectangle);

    return true;
}

bool Renderer::renderTextureWithCamera(Texture txt, Camera cam){
    SDL_Rect* srcRect = new SDL_Rect;
    *srcRect = cam.handleCameraPerspective(*(txt.textureRectangle));
    SDL_RenderCopy(global.renderer, txt.textureTexture, nullptr, srcRect);
    delete srcRect;
    return true;
}