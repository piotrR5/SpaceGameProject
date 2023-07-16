#ifndef ENGINE

#define ENGINE

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <map>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "utils/sg_math.hpp"
#include "utils/log.hpp"
#include "utils/config.hpp"


#include "rendering/texture.hpp"
#include "rendering/render.hpp"
#include "rendering/handleCamera.hpp"

#include "gui/gui.hpp"

#include "../../src/game/objectHandler.hpp"

using std::cout;
using std::endl;

struct Engine{
private:
    bool wasInitialised;


    uint16_t fps, desiredDT;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect* windowRectangle;

    Renderer rendererObject;
    Renderer rendererBackground;

    Camera camera;

    Gui gui;
    

    void eventHandler(bool& run);
    void onKeyPress(SDL_Event event, bool& run);
    void onKeyRelease(SDL_Event event, bool& run);
    void onMouseClick(SDL_Event event, bool& run);
    void onMouseRelease(SDL_Event event, bool& run);
    void onMouseScroll(SDL_Event event, bool& run);

    void fpsHandler(int start);


public:
    int getFps();
    void setFps(uint16_t fps);

    bool engineInit();
    
    void mainLoop();


    Engine();
    ~Engine();
};

#endif