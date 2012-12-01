#include "Graphics.h"
#include "App.h"
#include "Images.h"

Graphics::Graphics(App *parent) {
    this->parent = parent;
}

Graphics::~Graphics() {
    SDL_FreeSurface(screen);
    SDL_FreeSurface(buffer);

    if(SDL_WasInit(SDL_INIT_VIDEO))
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

bool Graphics::init() {
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    if(!SDL_WasInit(SDL_INIT_VIDEO))
        throw runtime_error("Could not initialization graphics");

    SDL_initFramerate(&fpsm);
    SDL_setFramerate(&fpsm, frameRate);
    
    screen_rect.x = screen_rect.y = 0;
    screen_rect.w = screenWidth;
    screen_rect.h = screenHeight;
#ifdef _PC_
    SDL_putenv((char*)"SDL_VIDEO_CENTERED=true");
    buffer = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
#else    
    SDL_ShowCursor(SDL_DISABLE);
    buffer = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 16, 0, 0, 0, 0);
#endif
    if(buffer == NULL)
        throw bad_alloc();

    screen = SDL_SetVideoMode(screenWidth, screenHeight, screenDepth, screenFlag);
    if (screen == NULL) 
        throw bad_alloc();
    
    SDL_WM_SetCaption(parent->getName().c_str(), NULL);

    lastTimer = SDL_GetTicks();

    return true;
}

void Graphics::updateScreen() {
    SDL_FillRect(buffer, NULL, 0);
    parent->draw();
#ifdef _PC_
    buffer2x = zoomSurface(buffer, 2.0, 2.0, SMOOTHING_OFF);
    if(buffer2x == NULL)
        throw bad_alloc();
    SDL_BlitSurface(buffer2x, 0, screen, &screen_rect);
    SDL_FreeSurface(buffer2x);
#else 
    SDL_BlitSurface(buffer, 0, screen, &screen_rect);
#endif        
    SDL_Flip(screen);
    if(SDL_GetTicks() - lastTimer >= 1000) {
        //cout << "FPS = " << fps << endl;
        fps = 0;
        lastTimer = SDL_GetTicks();
    }
    fps++;
    SDL_framerateDelay(&fpsm);
}
