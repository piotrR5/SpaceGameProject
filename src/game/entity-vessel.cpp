#include "entity-vessel.hpp"
#include "../../src/engine/utils/log.hpp"
#include <vector>

Vessel::Vessel()
{
    vec2 pos = {0,0};
    vesselRect.position = pos;
    vesselRect.A = {pos.x-vesselWidth/2,pos.y+vesselHeight/2};
    vesselRect.B = {pos.x+vesselWidth/2,pos.y+vesselHeight/2};
    vesselRect.C = {pos.x+vesselWidth/2,pos.y-vesselHeight/2};
    vesselRect.D = {pos.x-vesselWidth/2,pos.y-vesselHeight/2};
    pathFindingRadius = 0;
    armorType(light);
}
Vessel::Vessel(int pthR,vec2 pos, uint8_t arm, std::vector<part> segm, Texture& txt, SDL_Renderer* renderer)
{
    vesselRect.position = pos;
    vesselRect.A = {pos.x-vesselWidth/2,pos.y+vesselHeight/2};
    vesselRect.B = {pos.x+vesselWidth/2,pos.y+vesselHeight/2};
    vesselRect.C = {pos.x+vesselWidth/2,pos.y-vesselHeight/2};
    vesselRect.D = {pos.x-vesselWidth/2,pos.y-vesselHeight/2};
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
    segments = segm;
    shipTexture = txt;
}

vec2 Vessel::GetPosition()
{
    return vesselRect.position;
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
    default: logErr("Wrong flag !"); return false;
    }
}

rectangle Vessel::GetVesselRectangle()
{
    return vesselRect;
}