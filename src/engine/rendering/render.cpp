#include "render.hpp"

bool Renderer::initRenderer(SDL_Renderer* renderer, SDL_Rect* windowRect){
    this->renderer=renderer;
    if(this->renderer==nullptr){
        logErr("rendererObject renderer is nullptr");
        return false;
    }

    this->windowRectangle = windowRect;
    if(this->windowRectangle==nullptr){
        logErr("renderObject windowRectangle is nullptr");
        return false;
    }

    return true;
}

bool Renderer::basicRenderTexture(Texture txt){
    SDL_Rect* foo=new SDL_Rect;
    foo->x=txt.textureRectangle->x;
    foo->y=txt.textureRectangle->y;
    foo->w=txt.textureRectangle->w;
    foo->h=txt.textureRectangle->h;

    SDL_RenderCopy(renderer, txt.textureTexture, foo, windowRectangle);

    return true;
}

bool Renderer::renderTextureWithCamera(Texture txt, Camera cam){
    SDL_Rect* srcRect = new SDL_Rect;
    *srcRect = cam.handleCameraPerspective(*(txt.textureRectangle));
    SDL_RenderCopy(renderer, txt.textureTexture, txt.textureRectangle, srcRect);
    return true;
}