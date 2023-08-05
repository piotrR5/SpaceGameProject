#include "../utils/sg_math.hpp"

vec2 vec2::AddVec2(vec2 a, vec2 b)
{
    vec2 ret;
    ret.x = a.x+b.x;
    ret.y = a.y+b.y;
    return ret;
}
float DistanceBetweenPoints(vec2 start, vec2 end)
{
    return sqrt(pow(start.x-end.x,2)-pow(start.y-end.y,2));
}