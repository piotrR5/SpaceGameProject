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

bool Renderer::RenderObject(Object& obj, Camera cam)
{
    SDL_Rect* srcRect = new SDL_Rect;
    *srcRect = cam.handleCameraPerspective(*(obj.GetObjectTexture().textureRectangle));
    srcRect->x -= srcRect->w/2;
    srcRect->y -= srcRect->h/2;
    SDL_SetRenderDrawColor(global.renderer,255,255,255,255);
    SDL_RenderDrawRect(global.renderer,srcRect);
    SDL_SetRenderDrawColor(global.renderer,0,0,0,255);
    SDL_RenderCopyEx(global.renderer, obj.GetObjectTexture().textureTexture, nullptr, srcRect, obj.GetAngle(),nullptr,SDL_FLIP_NONE);
    delete srcRect;
    return true;
}

bool Renderer::RenderCollisonRects(Object& obj, Camera cam)
{
    SDL_SetRenderDrawColor(global.renderer,100,255,100,255);
    vec2 t[5] = {cam.ConvertToCameraCoords(obj.GetObjectRect().A),cam.ConvertToCameraCoords(obj.GetObjectRect().B),
    cam.ConvertToCameraCoords(obj.GetObjectRect().C),cam.ConvertToCameraCoords(obj.GetObjectRect().D),cam.ConvertToCameraCoords(obj.GetObjectRect().position)};
    SDL_RenderDrawLine(global.renderer,t[0].x,t[0].y,t[1].x,t[1].y);
    SDL_RenderDrawLine(global.renderer,t[1].x,t[1].y,t[2].x,t[2].y);
    SDL_RenderDrawLine(global.renderer,t[2].x,t[2].y,t[3].x,t[3].y);
    SDL_RenderDrawLine(global.renderer,t[3].x,t[3].y,t[0].x,t[0].y);
    SDL_SetRenderDrawColor(global.renderer,0,0,0,255);
    return true;
}