#include "entity-vessel.hpp"
#include "../../src/engine/utils/log.hpp"
#include <vector>

Vessel::Vessel(int pthR,rectangle VesselRectangle, uint8_t arm, Texture& txt) : Object(txt,VesselRectangle)
{
    pathFindingRadius = pthR;
    switch(arm)
    {
        case 0 : 
        armorType(light);
        break;
        case 1 :
        armorType(medium);
        break;
        case 2 :
        armorType(heavy);
        break;
        case 3 :
        armorType(shield);
        break;
        default :
        logErr("Wrong armor type ! Setting to light.");
        break;
    }
}

vec2 Vessel::GetPosition()
{
    return objectRectangle.position;
}

void Vessel::ModifyFlags(uint8_t flag)
{
    switch (flag)
    {
    case 1 :
        if(isVisible) isVisible = 0;
        else isVisible = 1;
        break;
    case 2 :
        if(isDestructible) isDestructible = 0;
        else isDestructible = 1;
        break;
    case 3 :
        if(isMoving) isMoving = 0;
        else isMoving = 1;
        break;
    case 4 :
        if(hasToMove) hasToMove = 0;
        else hasToMove = 1;
        break;
    case 5 :
        if(isSelected) isSelected = 0;
        else isSelected = 1;
    default:
        logErr("Wrong Flag !");
        break;
    }
}

bool Vessel::GetFlagState(uint8_t flag)
{
    switch (flag)
    {
    case 1 : return isVisible;
    case 2 : return isDestructible;
    case 3 : return isMoving;
    case 4 : return hasToMove;
    case 5 : return isSelected;
    default: logErr("Wrong flag !"); return false;
    }
}

rectangle Vessel::GetVesselRectangle()
{
    return objectRectangle;
}

uint8_t Vessel::GetVesselId()
{
    return id;
}

void Vessel::ChangeRectangle(rectangle newRect)
{
    objectRectangle = newRect;
    return;
}
uint8_t Vessel::GetVelocity()
{
    return velocity;
}