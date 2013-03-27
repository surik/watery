#ifndef LEVEL_H_
#define LEVEL_H_ 1

#include "deps.h"

class Images;
class Animations;

class Level {
    private:
        string tileMap[14], eventMap[14], levelName, nextLevelName;
        Images *parentImg;
        Animations *parentAnim;
        int time, startTime, limitTime, pauseTime;
        int trapMap[14][20], heroX, heroY;
        bool rendered, done;
        void render();

    public:
        Level(Images *parentImg, Animations *parentAnim);
        ~Level();

        bool open(string levelName);
        void draw();
        int collision(int x, int y, int w, int h);
        string getLevelName() {return levelName;}
        string getNextLevelName() {return nextLevelName;}
        bool getDone() {return done;}
        void setDone(bool done) {this->done = done;}
        int getTime() {return time - startTime - pauseTime;}
        int getTimeLimit() {return limitTime;}
        void setTime(Uint32 t) {time = t;} 
        void addPauseTime(int t) {pauseTime += t;} 
        int getHeroX() {return heroX;}
        int getHeroY() {return heroY;}
        void addTimeBonus();
        void next() { done = 1;}
};

#endif
