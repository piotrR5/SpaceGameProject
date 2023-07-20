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
    *temp=*(txt.textureRectangle);
    planetTextureGenerated.initTexture(txt.textureTexture, temp);
    planetTextureGenerated.textureRectangle->x=posX;
    planetTextureGenerated.textureRectangle->y=posY;
}
vec2 Planet::getPosition()
{
    return {posX,posY};
}
int Planet::getRadius()
{
    return planetRadius;
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
        default : 
        logErr("Wrong flag !");
        break;
    }
}
Texture Planet::getTexture()
{
    return planetTextureGenerated;
}