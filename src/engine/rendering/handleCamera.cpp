#include "handleCamera.hpp"

void Camera::initCamera(float x, float y){
    camera.x=x;
    camera.y=y;
    camera.w=1;
    camera.h=1;

    velocity = {0,0};
    logOK("camera created");
}

SDL_Rect Camera::handleCameraPerspective(SDL_Rect inputRectangle){
    SDL_Rect outputRectangle;
    outputRectangle.x=inputRectangle.x-camera.x + camera.w/2 + WINDOW_WIDTH/2;
    outputRectangle.y=inputRectangle.y-camera.y + camera.h/2 + WINDOW_HEIGHT/2;

    outputRectangle.w=camera.w*inputRectangle.w;
    outputRectangle.h=camera.h*inputRectangle.h;

    return outputRectangle;
}

void Camera::rescale(float arg){
    camera.w*=arg;
    camera.h*=arg;
}
void Camera::move(){
    camera.x+=velocity.x;
    camera.y+=velocity.y;
}
