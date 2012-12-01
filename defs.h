#ifndef DEFS_H_
#define DEFS_H_

// for graphics
const int frameRate = 30;
const int bufferWidth = 320;
const int bufferHeight = 240;
#ifdef _PC_
const int screenWidth = bufferWidth * 2;
const int screenHeight = bufferHeight * 2; 
const int screenDepth = 32;
const int screenFlag = SDL_HWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF;
#else
const int screenWidth = bufferWidth;
const int screenHeight = bufferHeight;
const int screenDepth = 16;
const int screenFlag = SDL_SWSURFACE;
#endif

//for audio
const int audioMaxSamples = 8;

// for controls
const int BTN_UP = SDLK_UP;
const int BTN_DOWN = SDLK_DOWN;
const int BTN_LEFT = SDLK_LEFT;
const int BTN_RIGHT = SDLK_RIGHT;
const int BTN_SELECT = SDLK_ESCAPE;
const int BTN_START = SDLK_RETURN;
#ifdef _PC_
const int BTN_A = SDLK_c;
const int BTN_B = SDLK_x;
const int BTN_X = SDLK_d;
const int BTN_Y = SDLK_s;
const int BTN_LS = SDLK_a;
const int BTN_RS = SDLK_f;
const int BTN_HOLD = SDLK_h;
#else
const int BTN_A = SDLK_LCTRL;
const int BTN_B = SDLK_LALT;
const int BTN_X = SDLK_SPACE;
const int BTN_Y = SDLK_LSHIFT;
const int BTN_LS = SDLK_TAB;
const int BTN_RS = SDLK_BACKSPACE;
const int BTN_HOLD = SDLK_PAUSE;
#endif

// directory for data files
const std::string dir_images = "data/images/";
const std::string dir_fonts = "data/fonts/";
const std::string dir_animations = "data/animations/";
const std::string dir_sounds = "data/sounds/";
const std::string dir_music = "data/music/";
const std::string dir_levels = "data/levels/";
const std::string file_hiscore = "data/hiscore";

#endif
