#ifndef MUSIC_H_
#define MUSIC_H_ 1

#include "deps.h"

class Audio;

class Music {
    private:
        map<string, Mix_Music *> music;
        Audio *parent;

    public:
        Music(Audio *parent);
        ~Music();
        
        Mix_Music *load(string name);
        bool loadMusic();
        void play(string name, int loop);
        void freeMusic(string name);
};


#endif
