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
    SDL_BlendMode(SDL_BLENDMODE_BLEND);
    initTTF_Font("assets/fonts/Oswald-Regular.ttf");

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
        panic("Window is nullptr");
    }else{
        logOK("Window created");
    }

    global.renderer= (SDL_CreateRenderer(window, -1, 0));
    if(global.renderer==nullptr){
        panic("renderer is nullptr");
    }else{
        logOK("renderer created");
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

    SDL_SetRenderDrawColor(global.renderer, 0, 0, 0, 255);
    SDL_RenderClear(global.renderer);
    SDL_RenderPresent(global.renderer);    

    srand(time(NULL));

    camera.initCamera(0,0);

    if(!rendererObject.initRenderer(windowRectangle)){
        panic("couldn't init rendererObject");
    }else{
        logOK("rendererObject created");
    }
    if(!rendererBackground.initRenderer(windowRectangle)){
        logErr("couldn't init rendererBackground");
        exit(0);
    }

    gui.initGui("assets/alphaTest.png",windowRectangle, 0, 0);
    Button b;
    b.initButton("button", "assets/button.jpg", gui.guiBackground.textureRectangle, nullptr, nullptr, 10, 10, 100, 50);
    gui.addButton(b);

    wasInitialised=true;
    return true;
}

void Engine::mainLoop(){
    bool run=true;
    log("main loop started");
    OH.addTexture("assets/planetTest.png");
    OH.addPlanet(Planet({3000,3000},0,0,500,OH.textures[0]));
    OH.addPlanet(Planet({0,0},0,0,500,OH.textures[0]));
    
    while(run){
        int startLoop=SDL_GetTicks();

        SDL_RenderClear(global.renderer);
        OH.moveObjects();
        if(gui.visible==false)eventHandler(run);
        else gui.eventHandler(run);

         for(auto& k : OH.planets)
         {
            rendererObject.renderTextureWithCamera(k.getTexture(),camera);
            SDL_RenderDrawPoint(global.renderer,camera.ConvertToCameraCoords(k.getPosition()).x,camera.ConvertToCameraCoords(k.getPosition()).y);
         }
        
        gui.renderGui();

        SDL_RenderPresent(global.renderer);

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