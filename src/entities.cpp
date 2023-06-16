#include "entities.hpp"


Entity::Entity(SDL_Renderer* renderer){
    position={500,500};
    speed={0,0};
    acceleration={0,0};
    orientation=0.0;
    texture={renderer, "assets/missingTexture.png", nullptr, nullptr};
    texture.backgroundRect=new SDL_Rect;
    texture.backgroundRect->h=20;
    texture.backgroundRect->w=20;
    texture.backgroundRect->x=position.x;
    texture.backgroundRect->y=position.y;

    texture.loadImage();
}

void EntityTexture::loadImage(){
    background=IMG_Load(src);
    if(background==nullptr){
        std::cout<<"error: couldn't load image: "<<SDL_GetError()<<"\n";
    }
    backgroundTexture=SDL_CreateTextureFromSurface(renderer, background);
}
