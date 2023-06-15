#include "graphics.hpp"

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
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    //window=SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
    window=SDL_CreateWindow(
        "TEST",
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        1024,
        576,
        SDL_WINDOW_SHOWN); 

    renderer=SDL_CreateRenderer(window, -1, 0);
    windowRect=new SDL_Rect;
    windowRect->h=576;
    windowRect->w=1024;
    windowRect->x=0;
    windowRect->y=0;

    SDL_Surface* icon = IMG_Load("assets/icons/icon.png");

    back1={renderer, "assets/background1.jpeg", nullptr, nullptr, windowRect};
    back1.loadImage();
    

    SDL_SetWindowIcon(window, icon);
    delete icon;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);    

    srand(time(NULL));

    mainLoop();
}

Engine::~Engine(){
    SDL_DestroyWindow(window);
    delete windowRect;
    TTF_Quit();
    SDL_Quit();
}


void Engine::eventHandler(bool& run){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            run = false;
            std::cout << "Quitting!\n";
            break;
        
        break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_q:{
                    run = false;
                    std::cout << "Quitting!\n";
                    break;
                }
                break;
            }
            printf( "Key press detected\n" );
            break;

        case SDL_KEYUP:
            printf( "Key release detected\n" );
            break;
        }
    }
}

bool Engine::mainLoop(){
    bool run=true;

    while(run){
        int startLoop=SDL_GetTicks();
        SDL_RenderClear(renderer);
        /*
            event handling
        */
        eventHandler(run);


        /**
         * draw here
        */

        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);

        SDL_RenderCopy(renderer, back1.backgroundTexture, NULL, back1.backgroundRect);
        SDL_RenderPresent(renderer);


        /**
         * 
        */



        //clearConsole();
        int dT = SDL_GetTicks64() - startLoop;
        std::string fps_text;
        if(dT)fps_text=" "+std::to_string((int)(1000/(float)(dT)));
        else fps_text=" 1000";
        //std::cout<<"[fps: "<<1000/(double)(dT+0.001)<<"]\n";
        if(dT<desiredDT){
            SDL_Delay(desiredDT-dT);
        }
    }

    return 0;
}

void Background::loadImage(){
    background=IMG_Load(src);
    if(background==nullptr){
        std::cout<<"error: couldn't load image: "<<SDL_GetError()<<"\n";
    }
    backgroundTexture=SDL_CreateTextureFromSurface(renderer, background);
}