#ifndef CAMERA

#define CAMERA

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

#include "../utils/log.hpp"
#include "../utils/config.hpp"
#include "../utils/sg_math.hpp"
#include "../globals.hpp"
#include "../utils/config.hpp"


struct Camera{
    vec2 position={0,0};
    vec2 velocity={0,0};
    float scale=1;

    void initCamera(float, float);

    SDL_Rect handleCameraPerspective(SDL_Rect inputRectangle);

    vec2 ConvertToWorldCoords(vec2 inputPoint);
    vec2 ConvertToCameraCoords(vec2 inputPoint);

    void rescale(float arg);
    void move();
};

#endif