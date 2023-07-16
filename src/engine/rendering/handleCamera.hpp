#ifndef CAMERA

#define CAMERA

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/log.hpp"
#include "../utils/config.hpp"
#include "../utils/sg_math.hpp"
#include "../globals.hpp"


struct Camera{
    SDL_FRect camera;
    vec2 velocity;

    void initCamera(float, float);

    SDL_Rect handleCameraPerspective(SDL_Rect inputRectangle);

    void rescale(float arg);
    void move();
};

#endif