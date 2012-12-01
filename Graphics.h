#ifndef GRAPHICS_H_
#define GRAPHICS_H_ 1

#include "deps.h"

class App;

class Graphics {
    private:
        App *parent;
        FPSmanager fpsm;
        SDL_Rect screen_rect;
        SDL_Surface *screen;
        SDL_Surface *buffer, *buffer2x;
        int fps, lastTimer;

    public:
        Graphics(App *parent);
        ~Graphics();
        
        bool init();
        void updateScreen();
        SDL_Surface *getBuffer() {return buffer;}
};


#endif
