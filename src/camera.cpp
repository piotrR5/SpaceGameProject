#include "camera.hpp"


void Camera::move(vec2 v){
    position.x+=v.x;
    position.y+=v.y;
}

void Camera::move(){
    position.x+=velocity.x;
    position.y+=velocity.y;
    velocity.x*=0.5;
    velocity.y*=0.5;
}