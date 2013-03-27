#include "Audio.h"
#include "App.h"

Audio::Audio(App *parent) {
    this->parent = parent;
    mix_isOpen = false;
}

Audio::~Audio() { 
    if(SDL_WasInit(SDL_INIT_AUDIO)) {
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        if(mix_isOpen) Mix_CloseAudio();
    }
}

bool Audio::init() {
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) != -1) {
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != -1) {
            mix_isOpen = true;
            Mix_AllocateChannels(audioMaxSamples);
        }
        else mix_isOpen = false; 
    }

    return mix_isOpen;
}

int Audio::resumeMusic() {
    if(Mix_PausedMusic()) {
        Mix_ResumeMusic();
        return true;
    } else return false;
}
