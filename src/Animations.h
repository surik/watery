#ifndef ANIMATION_H_
#define ANIMATION_H_ 1

#include "deps.h"

class Images;

class Animation {
    private:
        Images *parent;
        string name;
        int curFrame, numFrame, endFrame, *delayFrame; 

    public:
        Animation(Images *parent);
        ~Animation();        

        bool loadAnim(string fileName);
        void draw(int x, int y, bool loop);
        int getCurFrame() {return curFrame;}
        int getEndFrame() {return endFrame;}
        void reset() {curFrame = 0;}
};


class Animations {
    private:
        map<string, Animation *> animations;
        Images *parent;

    public:
        Animations(Images *parent);
        ~Animations();

        bool loadAnimations();
        void draw(string name, int x, int y, bool loop);
        void freeAnim(string name);
        bool end(string name) {return (animations[name]->getEndFrame() - animations[name]->getCurFrame()) > 0 ? false : true;}
        void reset(string name) {animations[name]->reset();}
};

#endif
