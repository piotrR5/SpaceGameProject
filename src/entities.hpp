#ifndef ENTITIES
#define ENTITIES

#include "utils.hpp"
#include "constants.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class EntityTexture{
    public:
    SDL_Renderer* renderer;
    std::string src{""};
    SDL_Surface *background;
    SDL_Texture* backgroundTexture;
    SDL_Rect* backgroundRect;
    void loadImage();
    EntityTexture();
    EntityTexture(SDL_Renderer* renderer,int16_t x, int16_t y, uint16_t w, uint16_t h,std::string src);
};

struct Entity{
public:
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    float128 orientation;
    float128 angularVelocity;
    EntityTexture texture;
    SDL_Point* rotation_axis;

    void move();
    void rotate(float128 rm);

    void update();


    Entity(SDL_Renderer* renderer);
    //{10,20}
};

#endif