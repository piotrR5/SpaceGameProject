#ifndef ENTITIES

#define ENTITIES

#include "utils.hpp"
#include "constants.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.hpp"
#include "log.hpp"

struct EntityFlags{
    bool isVisible;
    bool isMovable;
    bool isCollidable;
};

class Entity{
public:
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    float128 orientation;
    float128 angularVelocity;
    SDL_Point* rotation_axis;
    SDL_Renderer* renderer;

    Texture texture;

    EntityFlags flags;

    void render();

    Entity();
    Entity(SDL_Renderer* renderer);
    Entity(SDL_Renderer* renderer, vec2 position, vec2 velocity, vec2 acceleration, float128 orientation, const char* txtpath, EntityFlags flags);
    //{10,20}
};

#endif