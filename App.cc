#include "App.h"
#include "Graphics.h"
#include "Controls.h"
#include "Audio.h"
#include "Sounds.h"
#include "Music.h"
#include "Images.h"
#include "Font.h"
#include "Animations.h"
#include "Level.h"
#include "Hero.h"

App::App(string name) {
    this->name = name;
    appState = logo;
    done = 0;
    soundDie = false;

    graphics = new Graphics(this);
    controls = new Controls(this);
    audio = new Audio(this);
    sounds = new Sounds(audio);
    music = new Music(audio);
    images = new Images(graphics);
    font = new Font(graphics);
    animations = new Animations(images); 
    level = new Level(images, animations);
    hero = new Hero(controls, animations);
}

App::~App() {
    delete hero;
    delete level;
    delete font;
    delete animations;
    delete images;
    delete music;
    delete sounds;
    delete audio;
    delete graphics;
    delete controls;
    SDL_Quit();
}

bool App::init() {
    SDL_Init(0);
    srand(time(NULL));
    graphics->init();
    audio->init();
    sounds->loadSounds();
    music->loadMusic();
    images->loadImages();
    font->loadFont("LiberationMono-Regular", 12);
    animations->loadAnimations();
    ifstream file(file_hiscore.c_str());
    file >> hiScore;
    file.close();
    
    return true;
}

void App::start() {
    music->play("logo-music", -1);
    while(!done) {
        controls->getInput();
        processStates();
        graphics->updateScreen(); // app::draw
    }
}

void App::processStates() {
    int x, y, col, rnd;
    char num[2];

    if(controls->getSelectKey()) quit();
    //if(controls->getLsKey()) level->next();
    switch(appState) {
        case logo:
            score = 0;
            win = false;
            if(controls->getStartKey()) {
                appState = intro;
                nextLevelName = "level1";
                level->open(nextLevelName);
                hero->setLive(3);
                controls->allReset();
            }
            break;
        case intro:
            if (controls->getAnyKey()) {
                controls->allReset();
                appState = playing;
                hero->init(level->getHeroX(), level->getHeroY());
                rnd = rand () % 6 + 1;
                sprintf(num, "%d", rnd);
                audio->haltMusic();
                music->play("music"+string(num), -1);
            }
            break;
        case playing:
            hero->processInput();
            level->setTime(SDL_GetTicks());
            if(level->getTime() >= level->getTimeLimit()) {
                audio->haltMusic();
                hero->setLive(hero->getLive() - 1);
                appState = timeIsUp;
                break;
            }
            x = hero->getX() + hero->getNextFrameX();
            y = hero->getY() + hero->getNextFrameY();
            col = level->collision(x, y, hero->getW(), hero->getH());
            if(!col) {
                hero->addX(hero->getNextFrameX());
                hero->addY(hero->getNextFrameY());
            } else {
                if ((col == 2) || (col == 4) || (col == 3)){
                    if (!soundDie) {
                        sounds->play("die");
                        soundDie = true;
                    }
                    hero->setState(bursting);
                    break;
                } else if(col == 10) {
                    sounds->play("bonus");
                    level->addTimeBonus();
                } else if(col == 11) {
                    sounds->play("bonus");
                    if (hero->getLive() < 5)
                        hero->setLive(hero->getLive() + 1);
                }
            }
            if (col != 2 && col != 4 && col != 3) soundDie = false;
            if (hero->getState() == die) {
                soundDie =  false;
                appState = gameOver;
                audio->haltMusic();
                music->play("gameover1", 0);
                break;
            }
            if(level->getDone()) {
                score += (hero->getLive() * 100) + ((level->getTimeLimit() - level->getTime()) / 1000);
                nextLevelName = level->getNextLevelName();
                audio->haltMusic();
                if(nextLevelName != "gameover") {
                    level->open(nextLevelName);
                    appState = showScore;
                    controls->allReset();
                } else {
                    appState = gameOver;
                    win = true;
                    audio->haltMusic();
                    music->play("gameover2", 0);
                    break;
                }
            }
            if(controls->getStartKey()) {
                controls->allReset(); 
                appState = paused; 
                audio->pauseMusic();
                sounds->play("pause");
                pauseTime = SDL_GetTicks();
            }
            break;
        case showScore:
            if (controls->getAnyKey()) {
                controls->allReset();
                appState = playing;
                hero->init(level->getHeroX(), level->getHeroY());
                rnd = rand () % 6 + 1;
                sprintf(num, "%d", rnd);
                audio->haltMusic();
                music->play("music"+string(num), -1);
            }
            break;
        case timeIsUp:
            if(controls->getAnyKey()) {
                controls->allReset();
                if (hero->getLive() <= 0) appState = gameOver;
                else {
                    level->open(nextLevelName);
                    // тоже самое что и в showScore :(
                    appState = playing;
                    hero->init(level->getHeroX(), level->getHeroY());
                    rnd = rand () % 6 + 1;
                    sprintf(num, "%d", rnd);
                    audio->haltMusic();
                    music->play("music"+string(num), -1);
                }
            }
            break;
        case gameOver:
            if (score > hiScore) {
                hiScore = score;
                ofstream file(file_hiscore.c_str());
                file << hiScore;
                file.close();
            }
            if(controls->getStartKey()) {
                controls->allReset(); 
                appState = logo;
                music->play("logo-music", -1);    
            }
            break;
        case paused:
            if(controls->getStartKey()) {
                controls->allReset(); 
                appState = playing;
                sounds->play("pause");
                audio->resumeMusic();
                level->addPauseTime(SDL_GetTicks() - pauseTime);
            }
            break;
        default: break;
    }
}

void App::drawLogo() {
    images->draw("logo-background", 0, 0);
    animations->draw("logo-pressstart", 116, 150, 1);
}

void App::drawGame() {
    char text[11];
    
    level->draw();
    font->print(level->getLevelName(), 2, 2);
    for (int i = 0; i < hero->getLive(); i++)
        images->draw("bonus-live", 140+(i*14), 1);

    sprintf(text, "Time: %d", (level->getTime()) / 1000);
    font->print(text, 220, 2);
    hero->draw(); 
}

void App::drawScore() {
    int w, h, x, y;
    char text[20];
    string levelCompleted = "Level Completed";
    font->size(levelCompleted, w, h);
    x = (bufferWidth - w) / 2;
    y = (bufferHeight - h) / 2;
    font->print(levelCompleted, x, y);
    sprintf(text, "Score: %06d", score);
    font->size(text, w, h);
    x = (bufferWidth - w) / 2;
    y = (bufferHeight - h) / 2 + h;
    font->print(text, x, y);
}

void App::drawIntro() {
    int w, h, x, y;
    string str1 = "Watery remembered that he had promised";
    string str2 = "to water the cactus.";
    images->draw("intro", 70, 20);
    font->size(str1, w, h);
    x = (bufferWidth - w) / 2;
    font->print(str1, x, 190);
    font->size(str2, w, h);
    x = (bufferWidth - w) / 2;
    y = 190 + h;
    font->print(str2, x, y);
}

void App::drawGameOver() {
    int w, h, x, y, offset;
    char text[20];
    string gameover = "Game Over";

    if (win) offset = 50;
    else offset = 0;
    
    sprintf(text, "Hi score: %06d", hiScore);
    font->size(text, w, h);
    x = (bufferWidth - w) / 2;
    y = (bufferHeight - h) / 2 + h + offset;
    font->print(text, x, y);   
    
    sprintf(text, "Score: %06d", score);
    font->size(gameover, w, h);
    x = (bufferWidth - w) / 2;
    y = (bufferHeight - h) / 2 + offset;
    font->print(gameover, x, y);
    
    font->size(text, w, h);
    x = (bufferWidth - w) / 2;
    y = (bufferHeight - h) / 2 + 2 * h + offset;
    font->print(text, x, y);

    if (win)
        images->draw("outro", 89, offset/2);
}

void App::drawPause() {
    int w, h, x, y;
    string pause = "Pause";
    font->size(pause, w, h);
    x = (bufferWidth - w) / 2;
    y = (bufferHeight - h) / 2;
    font->print(pause, x, y);
}

void App::drawTimeIsUp() {
    int w, h, x, y;
    string timeisup = "Time is Up";
    font->size(timeisup, w, h);
    x = (bufferWidth - w) / 2;
    y = (bufferHeight - h) / 2;
    font->print(timeisup, x, y);
}

void App::draw() {
    switch(appState) {
        case logo :
            drawLogo();
            break;
        case intro:
            drawIntro();
            break;
        case playing:
            drawGame();
            break;
        case showScore:
            drawScore();
            break;
        case timeIsUp:
            drawTimeIsUp();
            break;
        case paused:
            drawPause();
            break;
        case gameOver:
            drawGameOver();
        default:
            break;
    }
}
