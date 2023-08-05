#ifndef ENTITY_PLANET
#define ENTITY_PLANET

#include <iostream>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../engine/rendering/texture.hpp"
#include "../engine/utils/sg_math.hpp"

class Planet
{
    private : 
    float posX, posY;
    Texture planetTextureGenerated;
    int planetRadius;
    int planetGravity;
    int planetElectromagneticField;
    uint8_t velocity;
    // Flags
    bool isSelected = false;
    bool isVisible = true;
    bool isDestructible = false;
    bool isMoving = false;
    bool hasToMove = false;

    public : 
    Planet(); // Generic constructor
    Planet(std::pair<int,int> position,int grav, int elf, int radius,const Texture& txt); // Specific constructor
    vec2 getPosition();
    int getRadius();
    void generateTexture();
    uint8_t getVelocity();
    Texture getTexture();
    void modifyFlags(uint8_t flag);
    bool getFlagState(uint8_t flag);
    void modifyPosition(int x, int y);
    void setPosition(int x, int y);

    bool operator==(const Planet& rhs) const;
};
#endif
