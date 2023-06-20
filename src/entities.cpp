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
    texture=EntityTexture(renderer, 0,0,ENTITY_SEGMENT_SIZE, ENTITY_SEGMENT_SIZE, "assets/entityMissingTexture.png");;
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
    background=IMG_Load(src.c_str());
    if(background==nullptr){
        std::cout<<"error: couldn't load image: "<<SDL_GetError()<<"\n";
    }
    backgroundTexture=SDL_CreateTextureFromSurface(renderer, background);
}

EntityTexture::EntityTexture(){
    backgroundRect=new SDL_Rect;
    backgroundRect->x=0;
    backgroundRect->y=0;
    backgroundRect->w=ENTITY_SEGMENT_SIZE;
    backgroundRect->h=ENTITY_SEGMENT_SIZE;
    src = "assets/entityMissingTexture.png";

 }
EntityTexture::EntityTexture(SDL_Renderer* renderer,int16_t x, int16_t y, uint16_t w, uint16_t h,std::string src){
    backgroundRect=new SDL_Rect;
    backgroundRect->x=x;
    backgroundRect->y=y;
    backgroundRect->w=w;
    backgroundRect->h=h;
    src = src;
}
