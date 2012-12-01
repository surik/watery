#ifndef HERO_H_
#define HERO_H_ 1

#include "deps.h"

class Controls;
class Animations;

enum {staying, moving, jumping, falling, bursting, die};
enum {leftWay, rightWay, upWay, downWay};

class Hero {
    private:
        Controls *parentCtrl;
        Animations *parentAnim;
        int x, y, w, h, startX, startY;
        int nextFrameX, nextFrameY;
        int state, direction, loopAnim;
        int live, stepMove;
        string curAnim;

    public:
        Hero(Controls *parentCtrl, Animations *parentAnim);
        ~Hero();

        void init(int x, int y);
        void processInput();
        void draw();
        int getX() {return x;}
        int getY() {return y;}
        int getW() {return w;}
        int getH() {return h;}
        void addX(int x0) {x += x0;}
        void addY(int y0) {y += y0;}
        int getNextFrameX() {return nextFrameX;}
        int getNextFrameY() {return nextFrameY;}
        void moveX(int dx) {nextFrameX = dx;}
        void moveY(int dy) {nextFrameY = dy;}
        int getState() {return state;}
        void setState(int s) {state = s;}
        int getLive() {return live;}
        void setLive(int l) {live = l;}
};


#endif
