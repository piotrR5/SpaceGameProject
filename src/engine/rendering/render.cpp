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
    SDL_SetRenderDrawColor(global.renderer,255,255,255,255);
    SDL_RenderDrawRect(global.renderer,srcRect);
    SDL_SetRenderDrawColor(global.renderer,0,0,0,255);
    SDL_RenderCopy(global.renderer, txt.textureTexture, nullptr, srcRect);
    delete srcRect;
    return true;
}