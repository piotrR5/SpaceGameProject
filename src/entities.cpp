#include "entities.hpp"

Entity::Entity(SDL_Renderer* renderer) {

    if(renderer==nullptr){
        log("Error: renderer is null");
        return;
    }

    position = { BACKGROUND_WIDTH / 2, BACKGROUND_HEIGHT / 2 };
    velocity = { 0, 0 };
    acceleration = { 0, 0 };
    orientation = 0.0;
    angularVelocity = 0.0;
    rotation_axis = new SDL_Point{ (int)position.x, (int)position.y };
    texture = Texture(renderer, position.x, position.y, ENTITY_SEGMENT_SIZE,
        ENTITY_SEGMENT_SIZE, ENTITY_MISSING_TEXTURE);

    texture.loadImage();

    log("Entity created");
}

Entity::Entity(
    SDL_Renderer* renderer, 
    vec2 position, 
    vec2 velocity,
    vec2 acceleration, 
    float128 orientation, 
    const char* txtpath,
    EntityFlags flags){

    if(renderer==nullptr){
        log("Error: renderer is null");
        return;
    }

    this->renderer=renderer;
    this->position=position;
    this->velocity=velocity;
    this->acceleration=acceleration;
    this->orientation=orientation;

    rotation_axis = new SDL_Point;
    texture = Texture(renderer, position.x, position.y, ENTITY_SEGMENT_SIZE,
        ENTITY_SEGMENT_SIZE, txtpath);
    texture.loadImage();

    log("Entity created");
}

Entity::Entity(){
    renderer=nullptr;
}