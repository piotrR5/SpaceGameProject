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

    keyStateMap = initKeyStateMap();

    camera.initCamera(0,0);

    if(!rendererObject.initRenderer(renderer, windowRectangle)){
        logErr("couldn't init rendererObject");
        exit(0);
    }

    wasInitialised=true;
    return true;
}

void Engine::eventHandler(bool& run){
    SDL_Event event;

    log(std::to_string(camera.velocity.y).c_str());
    camera.move();

    while (SDL_PollEvent(&event)) {

        bool ok;

        switch (event.type) {
        case SDL_QUIT:
            run = false;
            log("quitting");
        break;

        case SDL_KEYDOWN:
            ok = setState(keyStateMap, event.key.keysym.sym, true);

            if(!ok){
                char err[100];
                sprintf(err, "couldn't set key [%d] state", event.key.keysym.sym);
                logErr(err);
            }

        break;

        case SDL_KEYUP:
            ok = setState(keyStateMap, event.key.keysym.sym, false);
            
            if(!ok){
                char err[100];
                sprintf(err, "couldn't set key [%d] state", event.key.keysym.sym);
                logErr(err);
            }
        break;

        case SDL_MOUSEWHEEL:
            if(event.wheel.y > 0){
                camera.rescale(1.05);
            }else if(event.wheel.y < 0 ){
                camera.rescale(0.95);
            }
        
        }



        keyHandler(run);
    }
}

void Engine::keyHandler(bool& run){
    for(const auto& [key, state] : keyStateMap){
        if(key==SDLK_q && state==true){
            log("quitting");
            run=false;
            return;
        }
        if(key==SDLK_w && state==true){
            camera.velocity.y = -10;
        }
        if(key==SDLK_w && state==false){
            camera.velocity.y = 0;
        }
        if(key==SDLK_s && state==true){
            camera.velocity.y = 10;
        }
        if(key==SDLK_s && state==false){
            camera.velocity.y = 0;
            log("CHUJ");
        }
        if(key==SDLK_a && state==true){
            camera.velocity.x=-10;
        }
        if(key==SDLK_a && state==false){
            camera.velocity.x=0;
        }
        if(key==SDLK_d && state==true){
            camera.velocity.x=10;
        }
        if(key==SDLK_d && state==false){
            camera.velocity.x=0;
        }
        
        /*
            TUTAJ STWORZYSZ SOBIE LOGIKE PRZYCISKOW
        */
    }
}

void Engine::mainLoop(){
    bool run=true;
    log("main loop started");

    Texture txt;
    if(!txt.initTexture(renderer, "")){
        logErr("couldn't init texture");
        exit(0);
    }
    

    while(run){
        int startLoop=SDL_GetTicks();

        SDL_RenderClear(renderer);


        eventHandler(run);

        rendererObject.renderTextureWithCamera(txt, camera);

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