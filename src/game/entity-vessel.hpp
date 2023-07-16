#ifndef ENTITY_VESSEL
#define ENTITY_VESSEL

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../engine/rendering/texture.hpp"

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
    int pathFindingRadius;
    int pos_x,pos_y;
    const char* texture;
    enum armorType{light,medium,heavy,shield};
    std::vector<part> segments;
    Texture shipTexture;

    Vessel(); // Generic constructor
    Vessel(int pthR, int x, int y, uint8_t arm, std::vector<part> segm, const char* txtPath,SDL_Renderer* renderer); // Specfific constructor
};

#endif