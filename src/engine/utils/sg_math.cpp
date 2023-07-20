#include "../utils/sg_math.hpp"

vec2 vec2::AddVec2(vec2 a, vec2 b)
{
    vec2 ret;
    ret.x = a.x+b.x;
    ret.y = a.y+b.y;
    return ret;
}