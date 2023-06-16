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
        800,
        600,
        SDL_WINDOW_SHOWN); 

    renderer=SDL_CreateRenderer(window, -1, 0);
    windowRect=new SDL_Rect;
    windowRect->h=600;
    windowRect->w=800;
    windowRect->x=0;
    windowRect->y=0;

    SDL_Surface* icon = IMG_Load("assets/icons/icon.png");

    back1={renderer, "assets/debug1000x1000.png", nullptr, nullptr, windowRect};
    back1.backgroundRect->h=1000*camera.scale;
    back1.backgroundRect->w=1000*camera.scale;
    back1.backgroundRect->x=0;
    back1.backgroundRect->y=0;
    back1.loadImage();

    camera.scale=1.0;
    camera.position={0,0};
    

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

        case SDL_MOUSEWHEEL:
            printf( "MouseWheel movement detected\n" );
            if(event.wheel.y > 0)
            {
                camera.scale*=1.05;
                printf( "Camera scale is now: %.3f\n", camera.scale);
            }
            else if(event.wheel.y < 0)
            {
                printf( "Camera scale is now: %.3f\n", camera.scale);
                camera.scale*=0.95;
            }
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

        back1.backgroundRect->h=1000*camera.scale;
        back1.backgroundRect->w=1000*camera.scale;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        back1.backgroundRect->x=mouse_x-500*camera.scale;
        back1.backgroundRect->y=mouse_y-500*camera.scale;
        //back1.backgroundRect->x=-400*camera.scale+mouse_x;
        //back1.backgroundRect->y=-300*camera.scale+mouse_y;
        SDL_RenderCopy(renderer, back1.backgroundTexture,NULL, back1.backgroundRect);
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