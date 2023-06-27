#include "utils.hpp"

vec2 multiply(const vec2& v, float128 s){
    return {v.x*s, v.y*s};
}

float128 dotProduct(const vec2& v, const vec2& u){
    return {v.x * u.x + v.y * u.y};
}

float128 crossProduct(const vec2& v, const vec2& u){
    return {v.x*u.y - u.x*v.y};
}



matrix22 generateRotationMatrix(float128 arg){
    return {cos((float)arg), -sin((float)arg), sin((float)arg), cos((float)arg)};
}

vec2 multiply(const matrix22& m, const vec2& v){
    return vec2{m.xi*v.x+m.yi*v.y, m.xj*v.x + m.yj*v.y};
}
