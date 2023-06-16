#include "camera.hpp"


void Camera::move(vec2 v){
    position.x+=v.x;
    position.y+=v.y;
}