#ifndef GUI

#define GUI

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "../rendering/texture.hpp"
#include "../utils/config.hpp"
#include "../rendering/render.hpp"

#include <vector>
#include <tuple>

struct Button{
    const char* label;
    Texture texture;
    SDL_Rect* parentRect;
    void (*onClickHandler)(SDL_Event event);
    void (*onReleaseHandler)(SDL_Event event);

    bool initButton(SDL_Renderer* renderer, const char* label, const char* src, SDL_Rect* parentRect, void (*onClickHandler)(SDL_Event event),void (*onReleaseHandler)(SDL_Event event), int x, int y, int w, int h);

    void defaultButtonOnClick(SDL_Event event);
    void defaultButtonOnRelease(SDL_Event event);

    void renderButton();
};

struct Label{

};

struct Gui{
    bool visible;
    std::tuple<Texture, int, int> guiBackground;
    std::vector<Button>buttons;
    // std::map<Label, int, int>labels;
    std::vector<std::tuple<Texture, int, int>>images;


    bool initGui(SDL_Renderer* renderer, const char* src, SDL_Rect* winRect);
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
    SDL_Rect* windowRect;
    SDL_Renderer* renderer;
    bool inlineTextureRenderer();    
};


#endif