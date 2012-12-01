#include "Images.h"
#include "Graphics.h"

Images::Images(Graphics *parent) {
#ifdef _PC_    
   // IMG_Init(IMG_INIT_PNG);
#endif
    this->parent = parent;
}

Images::~Images() {
    map <string, SDL_Surface *>::iterator it;
    for(it = images.begin(); it != images.end(); ++it)
        freeImage((*it).first);
#ifdef _PC_
    IMG_Quit();
#endif
}

void Images::loadImages() {
    string name;
    int transparency;
    ifstream file((dir_images + "list").c_str());
    while(file) {
        file >> name >> transparency;
        if(!file.eof()) {
            SDL_Surface *surface = load(name.c_str(), bool(transparency));
            if(surface != NULL) images.insert(make_pair(name, surface));
            else return;           
        }
    } 
    file.close();
}

SDL_Surface *Images::load(string name, bool transparency) {
    freeImage(name);
    SDL_Surface *temp = IMG_Load((dir_images + name + ".png").c_str());
    if (temp == NULL)
        throw invalid_argument("Could not load graphic file: " + name);

    if (transparency)
        SDL_SetColorKey(temp, (SDL_SRCCOLORKEY | SDL_RLEACCEL), SDL_MapRGB(temp->format, 255, 0, 255));
   
    SDL_Surface *img ;
    img = SDL_DisplayFormat(temp); 
    if (img == NULL)
        throw bad_alloc();
    SDL_FreeSurface(temp);
    return img;
}

bool Images::insert(string name, SDL_Surface *surface) {
    bool ret = images.count(name) > 0 ? true : false;
    images.insert(make_pair(name, surface));
    return ret;
}

void Images::draw(string name, int x, int y) { 
    SDL_Rect rect = {x, y, images[name]->w, images[name]->h};
    SDL_BlitSurface(images[name], NULL, parent->getBuffer(), &rect);
}

void Images::freeImage(string name) {
    if(images.count(name) > 0)
        SDL_FreeSurface(images[name]);
    images.erase(name);
}
