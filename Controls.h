#ifndef CONTROLS_H_
#define CONTROLS_H_ 1

#include "deps.h"

class App;

class Controls {
    private:
        App *parent;
        bool aKeyPressed;
        bool bKeyPressed;
        bool xKeyPressed;
        bool yKeyPressed;
        bool lsKeyPressed;
        bool rsKeyPressed;
        bool upKeyPressed;
        bool downKeyPressed;
        bool leftKeyPressed;
        bool rightKeyPressed;
        bool startKeyPressed;
        bool selectKeyPressed;
        bool holdKeyPressed;
    
    public:
        Controls(App *parents);
        ~Controls();
        
        void getInput();
        void allReset();
        bool getAKey() {return aKeyPressed;}
        bool getBKey() {return bKeyPressed;}
        bool getXKey() {return xKeyPressed;}
        bool getYKey() {return yKeyPressed;}
        bool getLsKey() {return lsKeyPressed;}
        bool getRsKey() {return rsKeyPressed;}
        bool getUpKey() {return upKeyPressed;}
        bool getDownKey() {return downKeyPressed;}
        bool getLeftKey() {return leftKeyPressed;}
        bool getRightKey() {return rightKeyPressed;}
        bool getStartKey() {return  startKeyPressed;}
        bool getSelectKey() {return selectKeyPressed;}
        bool getHoldKey() {return holdKeyPressed;}
        bool getAnyKey() {return aKeyPressed || bKeyPressed || xKeyPressed || yKeyPressed 
                            || lsKeyPressed || rsKeyPressed || startKeyPressed;}
};

#endif
