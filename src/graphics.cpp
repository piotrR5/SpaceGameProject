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


    renderer=SDL_CreateRenderer(window, -1, 0);

    SDL_Surface* icon = IMG_Load("assets/icons/icon.png");
    SDL_SetWindowIcon(window, icon);
    delete icon;

    windowRect=new SDL_Rect;
    windowRect->h=SCREEN_HEIGHT;
    windowRect->w=SCREEN_WIDTH;
    windowRect->x=0;
    windowRect->y=0;
    camera.scale=1.0;
    camera.position={BACKGROUND_WIDTH/2,BACKGROUND_HEIGHT/2};

    Entity e1(renderer);
    Entity menuButton(renderer);
    entities.push_back(e1);
    entities.push_back(menuButton);

    back1={renderer, "assets/debug1000x1000.png", nullptr, nullptr, windowRect};
    back1.loadImage();

    this->loadSkybox();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);    

    skybox.backgroundRect=new SDL_Rect;
    loadSkybox("assets/skybox.png");

    srand(time(NULL));
    std::cout<<"Ryba 1"<<std::endl;
    mainMenuLoop();
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

       drawSkybox();

        camera.move();
        std::cout<<"[CAMERA]: "<<(double)camera.position.x<<" "<<(double)camera.position.y<<std::endl;

        drawSkybox();


        back1.backgroundRect->h=BACKGROUND_HEIGHT*camera.scale;
        back1.backgroundRect->w=BACKGROUND_WIDTH*camera.scale;
        back1.backgroundRect->x=-camera.position.x*camera.scale+SCREEN_WIDTH/2;
        back1.backgroundRect->y=-camera.position.y*camera.scale+SCREEN_HEIGHT/2;
        SDL_RenderCopy(renderer, back1.backgroundTexture,NULL, back1.backgroundRect);
        updateEntities();
        drawEntities();
        drawSquare(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 10);



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

bool Engine::mainMenuLoop()
{
    bool run = true;
    bool gameState = false;
    back1 = Background(renderer, 0,0,0,0,"assets/mainMenuBackground.png");
     std::cout<<"Ryba 2"<<std::endl;
    back1.backgroundRect = windowRect;
    //entities[1].texture = {renderer, "assets/button.jpg", nullptr,nullptr, entities[1].texture.backgroundRect};
    entities[1].texture= EntityTexture(renderer, SCREEN_WIDTH/2,SCREEN_HEIGHT/2, ENTITY_SEGMENT_SIZE, ENTITY_SEGMENT_SIZE, "assets/button.jpg");
    back1.loadImage();
    entities[1].texture.loadImage();
    while(run)
    {
        SDL_GetMouseState(&mouse_x, &mouse_y);
        int startLoop=SDL_GetTicks();
        SDL_RenderClear(renderer);
        mainMenuEventHandler(run,gameState);
        SDL_GetMouseState(&mouse_x, &mouse_y);
        back1.backgroundRect->h=SCREEN_HEIGHT;
        back1.backgroundRect->w=SCREEN_WIDTH;
        back1.backgroundRect->x=0;
        back1.backgroundRect->y=0;
        SDL_RenderCopy(renderer, back1.backgroundTexture,NULL, back1.backgroundRect);
        updateEntities();
        drawEntities();
        SDL_RenderPresent(renderer);
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
    if(gameState)
    {
        entities.pop_back();
        mainLoop();
    }
    return 0;
}

void Background::loadImage(){
    background=IMG_Load(src.c_str());
    if(background==nullptr){
        std::cout<<"error: couldn't load image: "<<SDL_GetError()<<"\n";
        IMG_Load("assets/entityMissingTexture.png");
    }
    backgroundTexture=SDL_CreateTextureFromSurface(renderer, background);
}

void Engine::drawEntities(){
    for(const auto& e:entities){
        if(!e.isVisible)continue;
        e.texture.backgroundRect->x=e.position.x*camera.scale+back1.backgroundRect->x;
        e.texture.backgroundRect->y=e.position.y*camera.scale+back1.backgroundRect->y;
        e.texture.backgroundRect->w=ENTITY_SEGMENT_SIZE*camera.scale;
        e.texture.backgroundRect->h=ENTITY_SEGMENT_SIZE*camera.scale;
        //SDL_RenderCopy(renderer, e.texture.backgroundTexture, NULL, e.texture.backgroundRect);
        SDL_RenderCopyEx(renderer,
                   e.texture.backgroundTexture,
                   NULL,
                   e.texture.backgroundRect,
                   e.orientation,
                   e.rotation_axis,
                   SDL_FLIP_NONE);
    }
}

void Engine::updateEntities(){
    for(auto& e:entities){
        e.update();
    }
}

void Engine::loadSkybox(){
    skybox.backgroundRect=new SDL_Rect;
    skybox.backgroundRect->x=0;
    skybox.backgroundRect->y=0;
    skybox.backgroundRect->w=SKYBOX_WIDTH;
    skybox.backgroundRect->h=SKYBOX_HEIGHT;

    skybox.src="assets/background1.jpeg";

    skybox.renderer=renderer;

    skybox.loadImage();
}

void Engine::drawSkybox(){
    SDL_RenderCopy(renderer, skybox.backgroundTexture, NULL , skybox.backgroundRect);
}



//TODO:
//interfejsy
//generalne uporzadkowanie