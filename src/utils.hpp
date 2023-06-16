#ifndef UTILS
#define UTILS

#include "constants.hpp"

struct vec2{
    float128 x,y;
};

struct matrix22{
    float128 a,b,c,d;
};

vec2 multiply(const matrix22& m, const vec2& v);

#endif