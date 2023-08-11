#ifndef ENTITY_VESSEL
#define ENTITY_VESSEL

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../engine/rendering/texture.hpp"
#include "../engine/utils/sg_math.hpp"

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
class Vessel
{
    private :
    int pathFindingRadius;
    rectangle vesselRect;
    const int vesselHeight = 100, vesselWidth = 50;
    enum armorType{light,medium,heavy,shield};
    std::vector<part> segments;
    Texture shipTexture;

    bool isVisible = true;
    bool isDestructible = true;
    bool isMoving = false;
    bool hasToMove = false;

    public :

    Vessel(); // Generic constructor
    Vessel(int pthR,vec2 pos, uint8_t arm, std::vector<part> segm, Texture& txt, SDL_Renderer* renderer); // Specfific constructor

    vec2 GetPosition();
    void ModifyFlags(uint8_t flag);
    bool GetFlagState(uint8_t flag);
    rectangle GetVesselRectangle();

};

#endif