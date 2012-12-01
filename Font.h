#ifndef FONT_H_
#define FONT_H_ 1

#include "deps.h"

class Graphics;

class Font {
    private:
        Graphics *parent;
        TTF_Font *font;
        SDL_Color color;

    public:
        Font(Graphics *parent);
        ~Font();
        
        bool loadFont(string fontName, int size);
        void setColor(int r, int g, int b) {color.r = r; color.g = g; color.b = b;}
        int size(string text, int &w, int &h) {return TTF_SizeText(font, text.c_str(), &w, &h);}
        void print(string text, int x, int y); 
};


#endif
