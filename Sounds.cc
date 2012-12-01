#include "Sounds.h"
#include "Audio.h"

Sounds::Sounds(Audio *parent) {
    this->parent = parent;
}

Sounds::~Sounds() {
    map <string, Mix_Chunk *>::iterator it;
    for(it = sounds.begin(); it != sounds.end(); ++it)
        freeSound((*it).first);
}

bool Sounds::loadSounds() {
    string name;
    ifstream file((dir_sounds + "list").c_str());
    if(!file.good())
        throw invalid_argument("Could not load sound list");
    
    while(file) {
        file >> name;
        if(!file.eof()) {
            Mix_Chunk *sample = load(name);
            if (sample != NULL) sounds.insert(make_pair(name, sample));
            else throw bad_alloc();
        }
    } 
    file.close();
    return true;
}

Mix_Chunk *Sounds::load(string name) {
    Mix_Chunk *sample = Mix_LoadWAV((dir_sounds + name + ".ogg").c_str());
    if (sample == NULL) bad_alloc(); 
    return sample;
}

void Sounds::play(string name) {
    Mix_PlayChannel(-1, sounds[name], 0);
}

void Sounds::freeSound(string name) {
    if(sounds.count(name) > 0)
        Mix_FreeChunk(sounds[name]);
}
