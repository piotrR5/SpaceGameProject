#include "texture.hpp"

void Texture::loadImage(){
    if(renderer==nullptr){
        log("renderer is null");
        return;
    }
    surface=IMG_Load(src);

    if(surface==nullptr){
        log(sprintf("error: couln`t load image: %s", SDL_GetError()));
        IMG_Load("assets/entityMissingTexture.png");
    }
    texture=SDL_CreateTextureFromSurface(renderer, surface);
    log("Image loaded correctly");
}

void Texture::loadImage(const char* src){
    this->src=src;
    if(renderer==nullptr){
        log("renderer is null");
        return;
    }
    surface=IMG_Load(src);

    if(surface==nullptr){
        log(sprintf("error: couln`t load image: %s", SDL_GetError()));
        IMG_Load("assets/entityMissingTexture.png");
    }
    texture=SDL_CreateTextureFromSurface(renderer, surface);
    log("Image loaded correctly");
}


Texture::Texture(){
    renderer=nullptr;
    log("Empty Texture created");
}

Texture::Texture(SDL_Renderer* renderer){
    this->renderer=renderer;
    this->rectangle=new SDL_Rect;
    log("Texture with renderer created");
}

Texture::Texture(SDL_Renderer* renderer, int16_t x, int16_t y, uint16_t w, uint16_t h,const char* src){
    this->renderer=renderer;
    this->src=src;
    SDL_Rect rect{x,y,w,h};
    this->rectangle=new SDL_Rect;
    *(this->rectangle)=rect;
    log("Texture created");
}

Texture::~Texture(){
    delete rectangle;
    delete surface;
    delete texture;
    delete [] src;
}