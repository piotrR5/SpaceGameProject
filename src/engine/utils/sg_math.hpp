#ifndef MATH

#define MATH

#include <math.h>
#include <algorithm>

struct vec2{
    float x,y;
    vec2 AddVec2(vec2 a, vec2 b);
};

struct matrix22{
    float xi, yi, xj, yj;
};
#endif