#include "texture.hpp"

bool Texture::initTexture(SDL_Renderer* renderer, const char* src){
    this->renderer=renderer;
    if(this->renderer==nullptr){
        logErr("renderer is nullptr");
        return false;
    }
    return loadTexture(src);
}

bool Texture::loadTexture(const char* src){
    this->textureSurface = IMG_Load(src);
    if(this->textureSurface == nullptr){
        if(src=="assets/missingTexture.png"){
            logErr("couldn't load missingTexture.png, quitting");
            exit(0);
        }
        logErr("couldn't load texture");
        log("Loading missing texture");
        loadTexture("assets/missingTexture.png");
    }
    textureRectangle=new SDL_Rect;
    textureRectangle->h = textureSurface->h;
    textureRectangle->w = textureSurface->w;
    textureRectangle->x = 0;
    textureRectangle->y = 0;

    if(textureRectangle ==nullptr){
        logErr("textureRectangle is nullptr");
        return false;
    }

    textureTexture = SDL_CreateTextureFromSurface(renderer, textureSurface);

    if(textureTexture == nullptr){
        logErr("textureTexture is nullptr");
        return false;
    }

    return true;
}

