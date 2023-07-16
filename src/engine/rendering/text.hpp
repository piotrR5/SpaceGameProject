#ifndef TEXT

#define TEXT

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../utils/log.hpp"
#include "texture.hpp"
#include "../globals.hpp"

Texture textureWithText(const char* label, SDL_Color color);

bool initTTF_Font(const char* src);



#endif