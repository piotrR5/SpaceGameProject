#ifndef GUI

#define GUI

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "../rendering/texture.hpp"
#include "../utils/config.hpp"
#include "../rendering/render.hpp"
#include "../rendering/text.hpp"
#include "../globals.hpp"

#include <vector>
#include <tuple>


struct Button{
    Texture texture;
    Texture label;
    SDL_Rect* parentRect;
    void (*onClickHandler)(SDL_Event event);
    void (*onReleaseHandler)(SDL_Event event);

    bool initButton(const char* label, const char* src, SDL_Rect* parentRect, void (*onClickHandler)(SDL_Event event),void (*onReleaseHandler)(SDL_Event event), int x, int y, int w, int h);

    void defaultButtonOnClick(SDL_Event event);
    void defaultButtonOnRelease(SDL_Event event);

    void renderButton();
};

struct Label{

};

struct Gui{
    bool visible;
    int x,y;
    Texture guiBackground;
    std::vector<Button>buttons;
    SDL_Rect* windowRect;


    bool initGui(const char* src, SDL_Rect* windowRect, int x, int y);
    void addButton(Button btn);
    void addTexture(Texture txt, int x, int y);

    bool renderGui();

    void eventHandler(bool& run);
    void onKeyPress(SDL_Event event, bool& run);
    void onKeyRelease(SDL_Event event, bool& run);
    void onMouseClick(SDL_Event event, bool& run);
    void onMouseRelease(SDL_Event event, bool& run);
    void onMouseScroll(SDL_Event event, bool& run);

    

private:
    bool inlineTextureRenderer();    
};


#endif