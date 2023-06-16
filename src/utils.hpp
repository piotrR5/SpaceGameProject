

#ifndef UTILS
#define UTILS

#include "constants.hpp"
#include <SDL2/SDL.h>
#include <math.h>

struct vec2{
    float128 x,y;
};

struct matrix22{
    float128 a,b,c,d;
};

vec2 multiply(const matrix22& m, const vec2& v);

void drawSquare(SDL_Renderer* renderer, int x, int y, int r);

matrix22 generateRotationMatrix(float128 arg);

#endif