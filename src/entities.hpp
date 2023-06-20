#ifndef ENTITIES
#define ENTITIES

#include "utils.hpp"
#include "constants.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct EntityTexture{
    SDL_Renderer* renderer;
    const char* src{""};
    SDL_Surface *background;
    SDL_Texture* backgroundTexture;
    SDL_Rect* backgroundRect;
    void loadImage();
};

class Entity{
public:
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    float128 orientation;
    float128 angularVelocity;
    EntityTexture texture;
    SDL_Point* rotation_axis;

    bool isVisible{1}, isMovable{1}, isCollidable{1};

    void move();
    void rotate(float128 rm);

    void update();


    Entity(SDL_Renderer* renderer);
    Entity(SDL_Renderer* renderer, vec2 position, vec2 velocity, vec2 acceleration, float128 orientation, const char* txtpath, bool isVisible, bool isMovable, bool isCollidable);
    //{10,20}
};

#endif