#ifndef AUDIO_H_
#define AUDIO_H_ 1

#include "deps.h"

class App;

class Audio {
    private:
        App *parent;
        bool mix_isOpen;
    
    public:
        Audio(App *parent);
        ~Audio();        

        bool init();
        void pauseMusic() {Mix_PauseMusic();}
        int resumeMusic();
        int haltMusic() {return Mix_HaltMusic();}
};


#endif
