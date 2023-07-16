#include "texture.hpp"

bool Texture::initTexture(const char* src){
    return loadTexture(src);
}

bool Texture::loadTexture(const char* src){
    SDL_Surface* surface = IMG_Load(src);
    if(surface == nullptr){
        if(src=="assets/missingTexture.png"){
            logErr("couldn't load missingTexture.png, quitting");
            exit(0);
        }
        logErr("couldn't load texture");
        log("Loading missing texture");
        loadTexture("assets/missingTexture.png");
    }
    textureRectangle=new SDL_Rect;
    textureRectangle->h = surface->h;
    textureRectangle->w = surface->w;
    textureRectangle->x = 0;
    textureRectangle->y = 0;

    if(textureRectangle ==nullptr){
        logErr("textureRectangle is nullptr");
        return false;
    }

    textureTexture = SDL_CreateTextureFromSurface(global.renderer, surface);

    if(textureTexture == nullptr){
        logErr("textureTexture is nullptr");
        return false;
    }

    return true;
}

bool Texture::initTexture(SDL_Texture* txt, SDL_Rect* rect){
    this->textureTexture=txt;
    this->textureRectangle=rect;
}


