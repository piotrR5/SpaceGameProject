#ifndef ENTITY_BACKGROUND

#define ENTITY_BACKGROUND

#include "entities.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class EntityBackground : public Entity{
public:
    EntityBackground(SDL_Renderer* renderer, const char* src);

    void loadBackground(const char* src);
};

#endif