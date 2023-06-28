#include "entity-background.hpp"

EntityBackground::EntityBackground(SDL_Renderer* renderer, const char* src){
    this->renderer=renderer;

    if(this->renderer==nullptr){
        log("Error: renderer inside EntityBackground is null");
        exit(0);
    }

    this->flags=EntityFlags{true, false, false};
    this->position={0,0};
    auto img=IMG_Load(src);
    this->texture=Texture(this->renderer, 0, 0, img->w, img->h, src);
    if(this->texture.renderer== nullptr ||
       this->texture.texture ==nullptr){
        log("Error: texture is invalid");    
    } 
    log("Background loaded succesfully");
}

void Entity::render(){
    SDL_RenderCopy(renderer, texture.texture, nullptr, texture.rectangle);
}