#include "Animations.h"
#include "Images.h"

Animation::Animation(Images *parent) {
    this->parent = parent;
    curFrame = 0;
}

Animation::~Animation() {
    delete[] delayFrame;
}

bool Animation::loadAnim(string fileName) {
    ifstream file((dir_animations + fileName).c_str());
    if (!file.good()) 
        throw invalid_argument("Could not load animation file: " + fileName);
    file >> name;
    file >> numFrame;
    delayFrame = new int[numFrame];
    for(int i = 0; i < numFrame; i++)
        file >> delayFrame[i];
    file >> endFrame;
    file.close();
    return true;
}

void Animation::draw(int x, int y, bool loop) {
    string image = name;
    char num[3];
    for (int i = 0; i < numFrame; i++) {
        if(curFrame >= delayFrame[i]) {
            sprintf(num, "%d", i+1);
            image = name + string(num, 2);
        }
    }
    parent->draw(image.c_str(), x, y);

    if (curFrame >= endFrame) {
        if (!loop) curFrame = endFrame;
        else curFrame = 0;
    }
    else curFrame++;
}

Animations::Animations(Images *parent) {
    this->parent = parent;
}

Animations::~Animations() {
    map <string, Animation *>::iterator it;
    for(it = animations.begin(); it != animations.end(); ++it)
        freeAnim((*it).first);
}

bool Animations::loadAnimations() {
    string temp;
    Animation *anim;
    
    ifstream file((dir_animations + "list").c_str());
    if (!file.good()) 
        throw invalid_argument("Could not load animations list file");
    
    while(file.good()) {
        file >> temp;
        if (!file.eof()) {
            anim = new Animation(parent);
            anim->loadAnim(temp);
            animations.insert(make_pair(temp, anim));
        }
    }
    file.close();

    return true;
}

void Animations::draw(string name, int x, int y, bool loop) {
    animations[name]->draw(x, y, loop);
}

void Animations::freeAnim(string name) {
    if(animations.count(name) > 0)
        delete animations[name];
}
