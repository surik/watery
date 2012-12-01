#include "App.h"
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        App game("Watery");
    
        game.init();
        game.start();
        
        return EXIT_SUCCESS;
    } catch(exception &e) {
        cerr << "Fatal error: " << e.what() << "." << endl;
    } catch(...) {
        cerr << "Unkown fatal error." << endl;
    }
    
    return EXIT_FAILURE;
}
