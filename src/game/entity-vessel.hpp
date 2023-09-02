#ifndef ENTITY_VESSEL
#define ENTITY_VESSEL

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../engine/rendering/texture.hpp"
#include "../engine/utils/sg_math.hpp"
#include "objects.hpp"

using namespace std;
struct weapon // Offensive weapons
{
    string name;
    string desc;
    uint8_t id;
    int power_usg;
    int range;
    int damage;
    int ap;
    bool attack_type;
};
struct systems //Engines, reactors, shield generators
{
    int power_usg;
    int power_production;
    int defence;
    int speed;
};
struct part // Ship segment
{
    enum position{center,front,back,left,right,topleft,topright,bottomleft,bottomright};
    vector<weapon> weapons;
    vector<systems> shipSystems;
};
class Vessel : public Object
{
    private :
    uint8_t id;
    uint8_t velocity;
    int pathFindingRadius;
    const int vesselHeight = 100, vesselWidth = 50;
    enum armorType{light,medium,heavy,shield};
    std::vector<part> segments;

    bool isVisible = true;
    bool isDestructible = true;
    bool isMoving = false;
    bool hasToMove = false;
    bool isSelected = false;

    public :

    Vessel(int pthR,rectangle vesselRectangle, uint8_t arm, Texture& txt); // Specfific constructor

    vec2 GetPosition();
    uint8_t GetVesselId();
    uint8_t GetVelocity();
    void ModifyFlags(uint8_t flag);
    bool GetFlagState(uint8_t flag);
    rectangle GetVesselRectangle();
    void ChangeRectangle(rectangle newRect);
};

#endif