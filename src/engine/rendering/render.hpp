#ifndef RENDER

#define RENDER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../utils/log.hpp"
#include "../utils/config.hpp"

#include "texture.hpp"
#include "handleCamera.hpp"

#include "../globals.hpp"

class Renderer{
    SDL_Rect* windowRectangle;
public:
    bool initRenderer(SDL_Rect* windowRect);

    bool basicRenderTexture(Texture txt);

    bool renderTextureWithCamera(Texture txt, Camera cam);
};

#endif