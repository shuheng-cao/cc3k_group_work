#include <iostream>
#include <memory>
#include "textdisplay.h"
#include "normal_controller.h"
#include "dlc_controller.h"

using namespace std;

int main (int argc, char* argv[]) {
    char c;
    TextDisplay d;
    
    d.displayFile("welcome.txt");

    while (cin >> c) {
        
        // normal controller
        if (c == 'n') {
            NormalController n_game;
            n_game.play();
            break;
            
        // dlc controller
        } else if (c == 'd') {
            DLCController dlc_game;
            dlc_game.play();
            break;
          
        // quit
        } else if (c == 'q') {
            break;
            
        // invalid input
        } else {
            cout << "Invaild input. Please choose again." << endl;
        }
    }
}
