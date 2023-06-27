#ifndef UTILS
#define UTILS

#include "constants.hpp"
#include <SDL2/SDL.h>
#include <math.h>

struct vec2{
    float128 x,y;
};

struct matrix22{
    float128 xi, yi, xj, yj;
};

vec2 multiply(const matrix22& m, const vec2& v);

vec2 multiply(const vec2& v, float128 s);

float128 dotProduct(const vec2& v, const vec2& u);

float128 crossProduct(const vec2& v, const vec2& u);

matrix22 generateRotationMatrix(float128 arg);

#endif