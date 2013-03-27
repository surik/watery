#include "Hero.h"
#include "Controls.h"
#include "Animations.h"

Hero::Hero(Controls *parentCtrl, Animations *parentAnim) {
    this->parentCtrl = parentCtrl;
    this->parentAnim = parentAnim;
    live = 3;
}

Hero::~Hero() {
}

void Hero::init(int x, int y) {
    this->x = x * 16;
    this->y = y * 16;
    this->startX = x;
    this->startY = y;
    this->w = 16;  this->h = 16;
    state = staying;
    direction = downWay;
    curAnim = "hero-upstaying";
}

void Hero::processInput() {
    moveX(0);
    moveY(0);
    switch(state) {
        case staying:
            if (direction == upWay) curAnim = "hero-upstaying";
            else if (direction == downWay) curAnim = "hero-downstaying";
            else if (direction == leftWay) curAnim = "hero-leftstaying";
            else curAnim = "hero-rightstaying";
            loopAnim = 1;
            if(parentCtrl->getRightKey()) state = moving;
            if(parentCtrl->getLeftKey())  state = moving;
            if(parentCtrl->getUpKey()) state = moving;
            if(parentCtrl->getDownKey())  state = moving;
            break;
        case moving:
            if (parentCtrl->getBKey()) stepMove = 4;
            else stepMove = 2;
            if(parentCtrl->getRightKey()) {
                moveX(stepMove);
                curAnim = "hero-rightmoving";
                loopAnim = 1;
                direction = rightWay;
            } else if(parentCtrl->getLeftKey()) {
                moveX(-stepMove);
                curAnim = "hero-leftmoving";
                loopAnim = 1;
                direction = leftWay;
            } else if(parentCtrl->getUpKey()) {
                moveY(-stepMove);
                curAnim = "hero-upmoving";
                loopAnim = 1;
                direction = upWay;
            } else if(parentCtrl->getDownKey()) {
                moveY(stepMove);
                curAnim = "hero-downmoving";
                loopAnim = 1;
                direction = downWay;
            } else state = staying;
            break;
        case bursting:
            if (!parentAnim->end("hero-bursting")) {
                curAnim = "hero-bursting";
                loopAnim = 0;
            } else {
                parentAnim->reset("hero-bursting");
                live--;
                if (live <= 0) {
                    parentAnim->reset("hero-bursting");
                    state = die;
                    break;
                }
                this->init(startX, startY);
            }
            break;
        case die:
            break;
        default: break;
    }
}

void Hero::draw() {
    parentAnim->draw(curAnim, x, y, loopAnim);
}
