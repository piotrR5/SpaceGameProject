#ifndef CAMERA

#define CAMERA

#include "utils.hpp"
#include "constants.hpp"

struct Camera{
    vec2 position;
    float128 scale=1.0;//default: 1 == 100%

    void move(vec2 v);
};


#endif