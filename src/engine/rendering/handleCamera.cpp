#include "handleCamera.hpp"

void Camera::initCamera(float x, float y){
    position.x=x;
    position.y=y;
    velocity = {0,0};
    logOK("camera created");
}

SDL_Rect Camera::handleCameraPerspective(SDL_Rect inputRectangle){
    SDL_Rect outputRectangle;
    outputRectangle.x=inputRectangle.x*scale-position.x*scale+WINDOW_WIDTH/2;
    outputRectangle.y=inputRectangle.y*scale-position.y*scale+WINDOW_HEIGHT/2;
    outputRectangle.w=inputRectangle.w*scale;
    outputRectangle.h=inputRectangle.h*scale;
    outputRectangle.x+=outputRectangle.w/2;
    outputRectangle.y+=outputRectangle.h/2;


    return outputRectangle;
}

void Camera::rescale(float arg){
    scale*=arg;
}
void Camera::move(){
    position.x+=velocity.x;
    position.y+=velocity.y;
}

vec2 Camera::ConvertToCameraCoords(vec2 inputPoint)
{
    vec2 ret;
    ret.x=inputPoint.x*scale-position.x*scale+WINDOW_WIDTH/2;
    ret.y=inputPoint.y*scale-position.y*scale+WINDOW_HEIGHT/2;
    return ret;
}

vec2 Camera::ConvertToWorldCoords(vec2 inputPoint)
{
    vec2 ret = inputPoint;
    ret.x-=WINDOW_WIDTH/2;
    ret.y-=WINDOW_HEIGHT/2;

    ret.x = (inputPoint.x + position.x)/scale;
    ret.y = (inputPoint.y + position.y)/scale;
    return ret;
}