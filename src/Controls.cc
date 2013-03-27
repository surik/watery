#include "Controls.h"
#include "App.h"

Controls::Controls(App *parent) {
    this->parent = parent;
    aKeyPressed = false;
    bKeyPressed = false;
    xKeyPressed= false;
    yKeyPressed = false;
    lsKeyPressed = false;
    rsKeyPressed = false;
    upKeyPressed = false;
    downKeyPressed = false;
    leftKeyPressed = false;
    rightKeyPressed = false;
    startKeyPressed = false;
    selectKeyPressed = false;
    holdKeyPressed = false;
} 

Controls::~Controls() {
}

void Controls::getInput() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                parent->quit();
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case BTN_UP:
                        upKeyPressed = true;
                        break;
                    case BTN_DOWN:
                        downKeyPressed = true;
                        break;
                    case BTN_LEFT:
                        leftKeyPressed = true;
                        break;
                    case BTN_RIGHT:
                        rightKeyPressed = true;
                        break;
                    case BTN_SELECT:
                        selectKeyPressed = true;
                        break;
                    case BTN_START:
                        startKeyPressed = true;
                        break;
                    case BTN_A:
                        aKeyPressed = true;
                        break;
                    case BTN_B:
                        bKeyPressed = true;
                        break;
                    case BTN_X:
                        xKeyPressed = true;
                        break;
                    case BTN_Y:
                        yKeyPressed = true;
                        break;
                    case BTN_LS:
                        lsKeyPressed = true;
                        break;
                    case BTN_RS:
                        rsKeyPressed = true;
                        break;
                    case BTN_HOLD:
                        holdKeyPressed = true;
                        break;
                    default: break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym) {
                    case BTN_UP:
                        upKeyPressed = false;
                        break;
                    case BTN_DOWN:
                        downKeyPressed = false;
                        break;
                    case BTN_LEFT:
                        leftKeyPressed = false;
                        break;
                    case BTN_RIGHT:
                        rightKeyPressed = false;
                        break;
                    case BTN_SELECT:
                        selectKeyPressed = false;
                        break;
                    case BTN_START:
                        startKeyPressed = false;
                        break;
                    case BTN_A:
                        aKeyPressed = false;
                        break;
                    case BTN_B:
                        bKeyPressed = false;
                        break;
                    case BTN_X:
                        xKeyPressed = false;
                        break;
                    case BTN_Y:
                        yKeyPressed = false;
                        break;
                    case BTN_LS:
                        lsKeyPressed = false;
                        break;
                    case BTN_RS:
                        rsKeyPressed = false;
                        break;
                    case BTN_HOLD:
                        holdKeyPressed = false;
                        break;
                    default: break;
                }
                break;
            default: break;
        }
    }
}

void Controls::allReset() {
    aKeyPressed = false;
    bKeyPressed = false;
    xKeyPressed= false;
    yKeyPressed = false;
    lsKeyPressed = false;
    rsKeyPressed = false;
    upKeyPressed = false;
    downKeyPressed = false;
    leftKeyPressed = false;
    rightKeyPressed = false;
    startKeyPressed = false;
    selectKeyPressed = false;
}
