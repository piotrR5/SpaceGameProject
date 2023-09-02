#include "entity-planet.hpp"

Planet::Planet(rectangle planetRectangle, int grav, int elf, int radius,Texture& txt) : Object(txt,planetRectangle)
{
    planetGravity = grav;
    planetRadius = radius;
    planetElectromagneticField = elf;
    velocity = 10;
}
vec2 Planet::getPosition()
{
    return objectRectangle.position;
}
int Planet::getRadius()
{
    return planetRadius;
}
uint8_t Planet::getVelocity()
{
    return velocity;
}
bool Planet::getFlagState(uint8_t flag)
{
    switch (flag)
    {
    case 1 : return isSelected;
    case 2 : return isVisible;
    case 3 : return isDestructible;
    case 4 : return isMoving;
    case 5 : return hasToMove;
    default : logErr("Wrong flag !"); break;
    }
    return false;
}
void Planet::modifyFlags(uint8_t flag)
{
    switch(flag)
    {
        case 1 :
        if(isSelected) isSelected=0;
        else isSelected = 1;
        break;
        case 2 :
        if(isVisible) isVisible=0;
        else isVisible = 1;
        break;
        case 3 :
        if(isDestructible) isDestructible=0;
        else isDestructible = 1;
        break;
        case 4 :
        if(isMoving) isMoving = 0;
        else isMoving = 1;
        break;
        case 5 : 
        if(hasToMove) hasToMove = 0;
        else hasToMove = 1;
        break;
        default : 
        logErr("Wrong flag !");
        break;
    }
}
Texture Planet::getTexture()
{
    return objectTexture;
}