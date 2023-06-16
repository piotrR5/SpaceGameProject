#include "camera.hpp"


void Camera::move(vec2 v){
    position.x+=v.x;
    position.y+=v.y;
}

void Camera::move(){
    position.x+=speed.x;
    position.y+=speed.y;
    speed.x*=0.5;
    speed.y*=0.5;
}