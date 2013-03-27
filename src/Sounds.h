#ifndef SOUNDS_H_
#define SOUNDS_H_ 1

#include "deps.h"

class Audio;

class Sounds {
    private:
        map<string, Mix_Chunk *> sounds;
        Audio *parent;

    public:
        Sounds(Audio *parent);
        ~Sounds();
        
        Mix_Chunk *load(string name);
        bool loadSounds();
        void play(string name);
        void freeSound(string name);
};


#endif
