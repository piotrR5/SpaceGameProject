#include "entity-planet.hpp"

Planet::Planet()
{
    posX = 0;
    posY = 0;
    planetRadius = 0;
    planetElectromagneticField = 0;
    planetGravity = 0;
}
Planet::Planet(std::pair<int,int> position, int grav, int elf, int radius,const Texture& txt)
{
    posX=position.first;
    posY=position.second;
    planetGravity = grav;
    planetRadius = radius;
    planetElectromagneticField = elf;
    SDL_Rect* temp = new SDL_Rect;
    temp->w = radius * 2;
    temp->h = radius * 2;
    *temp=*(txt.textureRectangle);
    planetTextureGenerated.initTexture(txt.textureTexture, temp);
    // planetTextureGenerated.textureRectangle->w=2*radius;
    // planetTextureGenerated.textureRectangle->h=2*radius;
    planetTextureGenerated.textureRectangle->x=posX-planetTextureGenerated.textureRectangle->w/2;
    planetTextureGenerated.textureRectangle->y=posY-planetTextureGenerated.textureRectangle->h/2;
    velocity = 10;
}
vec2 Planet::getPosition()
{
    return {posX,posY};
}
int Planet::getRadius()
{
    return planetRadius;
}
void Planet::modifyPosition(int x, int y)
{
    posX+=x;
    posY+=y;
    planetTextureGenerated.textureRectangle->x=posX-planetTextureGenerated.textureRectangle->w/2;
    planetTextureGenerated.textureRectangle->y=posY-planetTextureGenerated.textureRectangle->h/2;
}
void Planet::setPosition(int x, int y)
{
    posX=x;
    posY=y;
    planetTextureGenerated.textureRectangle->x=posX-planetTextureGenerated.textureRectangle->w/2;
    planetTextureGenerated.textureRectangle->y=posY-planetTextureGenerated.textureRectangle->h/2;
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
    return planetTextureGenerated;
}

bool Planet::operator==(const Planet& rhs) const
{return std::tie(posX,posY,planetGravity,planetRadius,planetElectromagneticField,velocity)
==std::tie(rhs.posX,rhs.posY,rhs.planetGravity,rhs.planetRadius,rhs.planetElectromagneticField,rhs.velocity);}