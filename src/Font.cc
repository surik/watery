#include "Font.h"
#include "Graphics.h"

Font::Font(Graphics *parent) {
    this->parent = parent;
    color.r = color.g = color.b = 255;    // по умолчанию всегда белый
    if(!TTF_WasInit()) TTF_Init();
    atexit(TTF_Quit);  // при завершение всей программы сделать TTF_Quit()
}

Font::~Font() {    
    TTF_CloseFont(font);
}

bool Font::loadFont(string fontName, int size) {
    font = TTF_OpenFont((dir_fonts + fontName + ".ttf").c_str(), size);
    if(font) return true;
    else
        throw invalid_argument("Could not load font: " + fontName);
}

void Font::print(string text, int x, int y) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == NULL)
        throw bad_alloc();
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_BlitSurface(surface, NULL, parent->getBuffer(), &rect);
    SDL_FreeSurface(surface);
}
