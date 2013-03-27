#include "Music.h"
#include "Audio.h"

Music::Music(Audio *parent) {
    this->parent = parent;
}

Music::~Music() {
    map <string, Mix_Music *>::iterator it;
    for(it = music.begin(); it != music.end(); ++it)
        freeMusic((*it).first);
}

bool Music::loadMusic() {
    string name;
    ifstream file((dir_music + "list").c_str());
    if(!file.good())
        throw invalid_argument("Could not load music list");

    while(file) {
        file >> name;
        if(!file.eof()) {
            Mix_Music *sample = load(name);
            if (sample != NULL) music.insert(make_pair(name, sample));
            else throw bad_alloc();
        }
    } 
    file.close();
    return true;
}

Mix_Music *Music::load(string name) {
    Mix_Music *sample = Mix_LoadMUS((dir_music + name + ".mod").c_str());
    if (sample == NULL)
        throw invalid_argument("Could not load music file: " + name);
    return sample;
}

void Music::play(string name, int loops) {
    Mix_PlayMusic(music[name], loops);
}

void Music::freeMusic(string name) {
    if(music.count(name) > 0)
        Mix_FreeMusic(music[name]);
}
