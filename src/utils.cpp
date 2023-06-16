#include "utils.hpp"



vec2 multiply(const matrix22& m, const vec2& v){
    return vec2{m.a*v.x+m.b*v.y, m.c*v.x + m.d*v.y};
}