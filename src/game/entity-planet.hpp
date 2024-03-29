#ifndef ENTITY_PLANET
#define ENTITY_PLANET

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../engine/rendering/texture.hpp"

class Planet
{
    private : 
    int posX, posY;
    Texture planetTextureGenerated;
    int planetRadius;
    int planetGravity;
    int planetElectromagneticField;
    // Flags
    bool isSelected = false;
    bool isVisible = true;
    bool isDestructible = false;

    public : 
    Planet(); // Generic constructor
    Planet(std::pair<int,int> position,int grav, int elf, int radius, Texture& txt); // Specific constructor
    std::pair<int,int> getPosition();
    int getRadius();
    void generateTexture();
    Texture getTexture();
    void modifyFlags(uint8_t flag);
};
#endif
