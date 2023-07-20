#include "entity-vessel.hpp"
#include "../../src/engine/utils/log.hpp"
#include <vector>

Vessel::Vessel()
{
    pos_x=0;
    pos_y=0;
    pathFindingRadius = 0;
    armorType(light);
}
Vessel::Vessel(int pthR, int x, int y, uint8_t arm, std::vector<part> segm, Texture& txt, SDL_Renderer* renderer)
{
    pos_x = x;
    pos_y = y;
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