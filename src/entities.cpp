#include "entities.hpp"


Entity::Entity(SDL_Renderer* renderer){
    position={BACKGROUND_WIDTH/2,BACKGROUND_HEIGHT/2};
    velocity={0,0};
    acceleration={0,0};
    orientation=0.0;
    angularVelocity=0.0;
    rotation_axis=new SDL_Point;
    rotation_axis->x=ENTITY_SEGMENT_SIZE/2;
    rotation_axis->y=ENTITY_SEGMENT_SIZE/2;
    texture={renderer, "assets/entityMissingTexture.png", nullptr, nullptr};
    texture.backgroundRect=new SDL_Rect;
    texture.backgroundRect->h=ENTITY_SEGMENT_SIZE;
    texture.backgroundRect->w=ENTITY_SEGMENT_SIZE;
    texture.backgroundRect->x=position.x;
    texture.backgroundRect->y=position.y;

    texture.loadImage();
}

void Entity::move(){
    position.x+=velocity.x;
    position.y+=velocity.y;
}
void Entity::rotate(float128 rm){
    orientation+=rm;
}

void Entity::update(){
    move();
    rotate(angularVelocity);
    velocity.x+=acceleration.x;
    velocity.y+=acceleration.y;
}

void EntityTexture::loadImage(){
    background=IMG_Load(src);
    if(background==nullptr){
        std::cout<<"error: couldn't load image: "<<SDL_GetError()<<"\n";
    }
    backgroundTexture=SDL_CreateTextureFromSurface(renderer, background);
}


