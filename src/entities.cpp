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
    bool isVisible, 
    bool isMovable, 
    bool isCollidable): 
        position(position), 
        velocity(velocity), 
        acceleration(acceleration),
        orientation(orientation), 
        isVisible(isVisible), 
        isMovable(isMovable),
        isCollidable(isCollidable) {


    rotation_axis = new SDL_Point;
    texture = Texture(renderer, position.x, position.y, ENTITY_SEGMENT_SIZE,
        ENTITY_SEGMENT_SIZE, ENTITY_MISSING_TEXTURE);
    texture.loadImage();

    log("Entity created");
}

void Entity::move() {
    position.x += velocity.x;
    position.y += velocity.y;
}

void Entity::rotate(float128 rm) { 
    orientation += rm; 
}

void Entity::update() {
    move();
    rotate(angularVelocity);
    velocity.x += acceleration.x;
    velocity.y += acceleration.y;
}