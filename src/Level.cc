#include "Level.h"
#include "Images.h"
#include "Animations.h"

Level::Level(Images *parentImg, Animations *parentAnim) {
    this->parentImg = parentImg;
    this->parentAnim = parentAnim;   
    this->limitTime = 240*1000; // 4 minuts
}


Level::~Level() {
    parentImg->freeImage("surfaceLevel");
}

bool Level::open(string levelName) {
    string str;
    parentImg->freeImage("surfaceLevel");
    done = false;
    
    ifstream file((dir_levels + levelName).c_str());
    if (!file.good())
        throw invalid_argument("Could not load level: " + levelName);

    getline(file, this->levelName, '\n');
    for(int i = 0; i < 14; i++) {
        getline(file, str, '\n');
        tileMap[i] = str;
    } 
    getline(file, str, '\n');
    heroX = atoi(str.substr(0, str.find(" ")).c_str()) - 1;
    heroY = atoi(str.substr(str.find(" ")).c_str());
    for(int i = 0; i < 14; i++) {
        getline(file, str, '\n');
        eventMap[i] = str;
    }
    getline(file, str, '\n');
    nextLevelName = str;
    file.close();
    
    for(int i = 0; i < 14; i++) {
        for(int j = 0; j< 20; j++) trapMap[i][j] = 0;
    }
    rendered = false;
    startTime = SDL_GetTicks();
    pauseTime = 0;
    return true;
}

void Level::render() {
    if (!rendered) {
        string temp;
        SDL_Rect rect;
        SDL_Surface *surfaceLevel;
    #ifdef _PC_
        surfaceLevel = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
    #else    
        surfaceLevel = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 16, 0, 0, 0, 0);
    #endif
        if (surfaceLevel == NULL)
            throw bad_alloc();

        for(int i = 0; i < 14; i++) {
            for(int j = 0; j < 20; j++) {
                temp = "block";
                temp += tileMap[i][j];
                rect.x = j * 16; rect.y = 16 + i * 16;
                rect.w = parentImg->getImage(temp)->w; rect.h = parentImg->getImage(temp)->h;
                SDL_BlitSurface(parentImg->getImage(temp), NULL, surfaceLevel, &rect);
            }
        }
        rendered = true;        
        parentImg->insert("surfaceLevel", surfaceLevel);
    }
}

void Level::draw() {
    render();
    parentImg->draw("surfaceLevel", 0, 0);
    for(int i = 0; i < 14; i++) {
        for(int j = 0; j < 20; j++) {
            if(eventMap[i][j] >= '1' && eventMap[i][j] <= '3') {
                int t = (eventMap[i][j] - '0') * 1000 + 1000;
                if((getTime() % t > 0) && (getTime() % t < 1000)) {
                    trapMap[i][j] = 2;  // slow trap
                    parentImg->draw("trap-slow2", j*16, i*16+16); 
                } else { 
                    trapMap[i][j] = 0;
                    parentImg->draw("trap-slow1", j*16, i*16+16);                
                }
            }
            if(eventMap[i][j] >= '4' && eventMap[i][j] <= '6') {
                int t = (eventMap[i][j] - '3') * 1000 + 0;
                if((getTime() % t > 0) && (getTime() % t < 500)) {
                    trapMap[i][j] = 3; // fast trap
                    parentImg->draw("trap-fast2", j*16, i*16+16);                 
                } else {
                    trapMap[i][j] = 0;
                    parentImg->draw("trap-fast1", j*16, i*16+16);
                }
            }
            if(eventMap[i][j] >= '7' && eventMap[i][j] <= '8') {
                int t = (eventMap[i][j] - '6') * 1000 + 1000;
                if((getTime() % t > 0) && (getTime() % t < 1000)) {
                    trapMap[i][j] = 4; // knife
                    if (eventMap[i][j] == '7')
                        parentImg->draw("trap-leftknife", j*16, i*16+16);                 
                    else if (eventMap[i][j] == '8')
                        parentImg->draw("trap-rightknife", j*16, i*16+16);
                } else trapMap[i][j] = 0;
            }
            if(eventMap[i][j] == 'L') parentImg->draw("bonus-live", j*16, i*16+16);            
            if(eventMap[i][j] == 'T') parentImg->draw("bonus-time", j*16, i*16+16);
            if(eventMap[i][j] == 'C') parentImg->draw("cactus", j*16, i*16+16);
        }
    }
}

int Level::collision(int x, int y, int w, int h) {
    int x2 = x + w;
    int y2 = y + h;
    if ((x < 0) || (y < 16) || (x > bufferWidth) || (y > bufferHeight-16)) return 1;
    for(int i = 0; i < 14; i++) {
        for(int j = 0; j < 20; j++) {
            int tx = j * 16;
            int ty = i * 16 + 16;
            int tx2 = tx + 16;
            int ty2 = ty + 16;
            if(tileMap[i][j] == '2') ty2 -= 8;
            if(eventMap[i][j] == 'T' || eventMap[i][j] == 'L') {tx +=8; tx2 -= 8; ty += 8; ty2 -= 8;}
            if(eventMap[i][j] == '7' || eventMap[i][j] == '8') {ty += 6; ty2 -= 6;}
            if(eventMap[i][j] >= '1' && eventMap[i][j] <= '6') {
                 ty2 -= 10; tx2 -= 4;
                 ty += 0; tx += 6;
            }
            if ((x < tx2) && (y < ty2) && (tx < x2) && (ty < y2)) {
                if((eventMap[i][j] == '9') || (eventMap[i][j] == 'C')) done = true;
                if(eventMap[i][j] == 'T') {
                    eventMap[i][j] = '0';
                    return 10; // bonus time
                }
                if(eventMap[i][j] == 'L') {
                    eventMap[i][j] = '0';
                    return 11; // bonus live
                }
                if(trapMap[i][j]) return trapMap[i][j];
                if(tileMap[i][j] > '0') return 1; // collision
            }
        }
    }
    return 0; // no collision
}

void Level::addTimeBonus() {
    startTime += 10*1000;
    if (getTime() < 0) startTime = SDL_GetTicks();
}
