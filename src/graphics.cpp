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

    float argument=0.0;

    back1 = Background(renderer, 0,0,0,0,"assets/background1.jpeg");
    back1.backgroundRect = windowRect;
    back1.loadImage();

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
    for(auto& e:entities){
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

void Engine::loadSkybox(std::string src){
    skybox.src=src;
    skybox.loadImage();
    if(skybox.background==nullptr){
        std::cout<<"error: couldn't load image: "<<SDL_GetError()<<"\n";
    }
    skybox.backgroundTexture=SDL_CreateTextureFromSurface(renderer, skybox.background);

}

void Engine::drawSkybox(){
    auto& sky = skybox;

    sky.backgroundRect->x=-SKYBOX_WIDTH/2;
    sky.backgroundRect->y=-SKYBOX_HEIHGT/2;
    sky.backgroundRect->w=2000;
    sky.backgroundRect->h=2000;
    SDL_RenderCopy(renderer,
                   sky.backgroundTexture,
                   NULL,
                   sky.backgroundRect);
}

Background::Background(){
    backgroundRect=new SDL_Rect;
    backgroundRect->x=0;
    backgroundRect->y=0;
    backgroundRect->w=ENTITY_SEGMENT_SIZE;
    backgroundRect->h=ENTITY_SEGMENT_SIZE;
    src = "assets/entityMissingTexture.png";

 }
Background::Background(SDL_Renderer* renderer, int16_t x, int16_t y, uint16_t w, uint16_t h,std::string src){
    backgroundRect=new SDL_Rect;
    backgroundRect->x=x;
    backgroundRect->y=y;
    backgroundRect->w=w;
    backgroundRect->h=h;
    src = src;
}