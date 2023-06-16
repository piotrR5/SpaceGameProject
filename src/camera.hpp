#ifndef CAMERA

#define CAMERA

#include "utils.hpp"
#include "constants.hpp"

struct Camera{
    vec2 position;
    vec2 velocity;
    float128 scale=1.0;//default: 1 == 100%

    void move(vec2 v);
    void move();
};


#endif