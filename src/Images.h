#ifndef IMAGES_H_
#define IMAGES_H_ 1

#include "deps.h"

class Graphics;

class Images {
    private:
        map<string, SDL_Surface*> images;
        Graphics *parent;

    public:
        Images(Graphics *parent);
        ~Images();
        
        SDL_Surface *load(string name, bool transparency);
        SDL_Surface *getImage(string name) {return images[name];}
        void loadImages();
        bool insert(string name, SDL_Surface *surface);
        void draw(string name, int x, int y);
        void freeImage(string name);
};


#endif
