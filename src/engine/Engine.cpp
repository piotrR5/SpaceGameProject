#include "Engine.hpp"
#ifdef __linux__ 

    //linux code goes here
    void clearConsole(){
        system("clear");
    }

#elif _WIN32
    // windows code goes here
    void clearConsole(){
        system("cls");
    }
#else

#endif

Engine::Engine(){
    log("Engine initialization started");
    bool ok=engineInit();
    if(ok)logOK("Engine initialized");
    else{
        logErr("Engine initialization failed");
        exit(0);
    }
}

bool Engine::engineInit(){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    fps=60;
    desiredDT=1000/fps;
 
    window=SDL_CreateWindow(
        "SPACE GAME by PEDROS & KOYOTOS",
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    ); 

    if(window==nullptr){
        logErr("Window is nullptr");
        return false;
    }

    renderer=SDL_CreateRenderer(window, -1, 0);

    if(renderer==nullptr){
        logErr("renderer is nullptr");
        return false;
    }

    SDL_Surface* icon = IMG_Load("assets/icons/icon.png");
    SDL_SetWindowIcon(window, icon);
    delete icon;

    windowRectangle=new SDL_Rect;
    windowRectangle->h=1000;
    windowRectangle->w=1000;
    windowRectangle->x=0;
    windowRectangle->y=0;

    if(windowRectangle==nullptr){
        logErr("windowRectangle is nullptr");
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);    

    srand(time(NULL));

    camera.initCamera(0,0);

    if(!rendererObject.initRenderer(renderer, windowRectangle)){
        logErr("couldn't init rendererObject");
        exit(0);
    }
    if(!rendererBackground.initRenderer(renderer, windowRectangle)){
        logErr("couldn't init rendererBackground");
        exit(0);
    }

    gui.initGui(renderer, "assets/menuTest.png",windowRectangle);
    Button b;
    b.initButton(renderer, "button", "assets/button.jpg", std::get<0>(gui.guiBackground).textureRectangle, nullptr, nullptr, 10, 10, 100, 50);
    gui.addButton(b);

    wasInitialised=true;
    return true;
}

void Engine::mainLoop(){
    bool run=true;
    log("main loop started");
    Planet testPlanet({10,10},"assets/planetTest.png",0,0,100);
    while(run){
        int startLoop=SDL_GetTicks();
        
        SDL_RenderClear(renderer);
        rendererObject.renderTextureWithCamera(testPlanet.generateTexture(renderer),camera);

        if(gui.visible==false)eventHandler(run);
        else gui.eventHandler(run);

        gui.renderGui();

        SDL_RenderPresent(renderer);

        fpsHandler(startLoop);
    }

    log("main loop ended");
}

void Engine::fpsHandler(int start){
    int dT = SDL_GetTicks64() - start;
    if(dT<desiredDT){
        SDL_Delay(desiredDT-dT);
    }
}


Engine::~Engine(){
    SDL_DestroyWindow(window); 
    delete windowRectangle;
    TTF_Quit();
    SDL_Quit();
}