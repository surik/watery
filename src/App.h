#ifndef APP_H_
#define APP_H_ 1

#include "deps.h"

class Graphics;
class Controls;
class Audio;
class Sounds;
class Music;
class Images;
class Font;
class Animations;
class Level;
class Hero;

enum {logo, intro, playing, showScore, timeIsUp,paused, gameOver};

class App {
    private:
        string name, nextLevelName;
        bool done, soundDie, win;
        int appState, pauseTime;
        int score, hiScore;
        Graphics *graphics;
        Controls *controls;
        Audio *audio;
        Sounds *sounds;
        Music *music;
        Images *images;
        Font *font; // для примера, может быть несколько шрифтоd
        Animations *animations; // для примера, может быть несколько анимаций
        Level *level;
        Hero *hero;

        void processStates();
        void drawLogo();
        void drawIntro();
        void drawGame();
        void drawScore();
        void drawTimeIsUp();
        void drawGameOver();
        void drawPause();

    public:
        App(string name);
        ~App();
        
        bool init();
        void start();
        void draw();
        void quit() {done = true;}

        string getName() {return name;}
        Images *getImages() {return images;}
};


#endif
