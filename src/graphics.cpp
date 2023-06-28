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
 
    window=SDL_CreateWindow(
        "SPACE GAME by PEDROS & KOYOTOS",
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    ); 

    if(window==nullptr){
        log("Error: window couldn't be created");
        exit(0);
    }
    log("window created succesfully");


    renderer=SDL_CreateRenderer(window, -1, 0);

    if(renderer==nullptr){
        log("Error: renderer couldn't be created");
        exit(0);
    }
    log("renderer created succesfully");

    SDL_Surface* icon = IMG_Load("assets/icons/icon.png");

    if(icon==nullptr){
        log("Error: icon couldn't be loaded");
    }else{
        SDL_SetWindowIcon(window, icon);
        log("icon loaded succesfully");
    }
    delete icon;

    windowRect=new SDL_Rect;
    windowRect->h=SCREEN_HEIGHT;
    windowRect->w=SCREEN_WIDTH;
    windowRect->x=0;
    windowRect->y=0;
    camera.scale=1.0;
    camera.position={BACKGROUND_WIDTH/2,BACKGROUND_HEIGHT/2};

    back = EntityBackground(renderer, "assets/skybox.png");

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
                case SDLK_q:
                    run = false;
                    std::cout << "Quitting!\n";
                break;

                case SDLK_w:
                    if(camera.position.y > -10)camera.velocity.y=-CAMERA_SPEED;
                break;
                
                case SDLK_s:
                    if(camera.position.y < BACKGROUND_HEIGHT + 10) camera.velocity.y=CAMERA_SPEED;
                break;

                case SDLK_a:
                    if(camera.position.x > -10)camera.velocity.x=-CAMERA_SPEED;
                break;
                
                case SDLK_d:
                    if(camera.position.x < BACKGROUND_WIDTH + 10)camera.velocity.x=CAMERA_SPEED;
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
                if(camera.scale<4.0)camera.scale*=(1+CAMERA_SCALE_FACTOR);
                printf( "Camera scale is now: %.3f\n", (double)camera.scale);
            }
            else if(event.wheel.y < 0)
            {
                
                if(camera.scale>0.5)camera.scale*=(1-CAMERA_SCALE_FACTOR);
                printf( "Camera scale is now: %.3f\n", (double)camera.scale);
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

        SDL_GetMouseState(&mouse_x, &mouse_y);
        /**
         * draw here
        */

        back.render();

        camera.move();

        
        log("CHECK1");


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

void Engine::mainMenuEventHandler(bool& run, bool& start){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            run = false;
            std::cout << "Quitting!\n";
        break;
        
        case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT :
                    if(mouse_x<SCREEN_WIDTH/2+10 && mouse_x>SCREEN_WIDTH/2-10 && mouse_y<SCREEN_HEIGHT/2+10 && mouse_y>SCREEN_HEIGHT/2-10)
                    {
                        run = false;
                        start = true;
                    }
                    break;
                case SDL_BUTTON_RIGHT:
                    break;
            }
        break;

        case SDL_KEYUP:
            printf( "Key release detected\n" );
        break;
        }
    }
}