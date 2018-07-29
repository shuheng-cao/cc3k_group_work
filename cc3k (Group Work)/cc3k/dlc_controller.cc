#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <curses.h>
#include "textdisplay.h"
#include "grid.h"
#include "type.h"
#include "dlc_controller.h"
using namespace std;


// display the content in filename
int display(string filename) {
    ifstream myFile(filename);
    string line;
    int y = 2;

    while (!myFile.eof()) {
        getline(myFile, line);
        mvaddstr(y, 0, line.c_str());
        y++;
    }
    
    return y;
}


// play a new game
void newGame(shared_ptr<TextDisplay> d, shared_ptr<Grid> g) {
    char race;
    PCType type;
    
    // select pc character race
    int y = display("selectPCdlc.txt");
    race = getch();

    while (true) {
        if (race == 's') {
            type = PCType::SHADE;
            break;
        } else if (race == 'd') {
            type = PCType::DROW;
            break;
        } else if (race == 'v') {
            type = PCType::VAMPIRE;
            break;
        } else if (race == 't') {
            type = PCType::TROLL;
            break;
        } else if (race == 'g') {
            type = PCType::GOBLIN;
            break;
        } else if (race == 'w') {
            type = PCType::WITCH;
            break;
        } else {
            mvaddstr(y, 0, "Invaild choice. Please choose again.");
            y++;
            cin >> race;
        }
    }
    
    // initilize game
    g->initGame("emptyfloor.txt", type);
  
    clear();
    mvaddstr(0, 0, d->print().c_str());
}


// transfer char dir into Direction type
Direction direction(char dir) {
    if (dir == 'w') {
        return Direction::N;
    } else if (dir == 'a') {
        return Direction::W;
    } else if (dir == 's') {
        return Direction::S;
    } else {
        return Direction::E;
    }
}


// play the game in dlc version
void DLCController::play() {
    shared_ptr<Grid> g = make_shared<Grid>();
    shared_ptr<TextDisplay> d = make_shared<TextDisplay>();
    g->setDisplay(d);
    
    char key;
    bool gameEnd = false;
    
    initscr();
    mvaddstr(0, 0, "In the DLC version, you will play with WASD controls.");
    newGame(d, g);
    
    while (true) {
        key = getch();
        char dir;
        
        // uses the potion in the direction
        if (key == 'u') {
            dir = getch();
            g->PCPickUp(direction(dir));
            
        // attacks the enemy in the direction
        } else if (key == 't') {
            dir = getch();
            g->PCAttack(direction(dir));
            
        // stops enemies from moving until this key is pressed again
        } else if (key == 'f') {
            g->toggleFrozen();
            
        // restarts the game
        } else if (key == 'r') {
            clear();
            refresh();
            newGame(d, g);
            continue;
            
        // quit the game
        } else if (key == 'q') {
            break;
            
        // moves in the direction pressed
        } else if ((key == 'w') || (key == 'a')
                   || (key == 's') || (key == 'd')) {
            g->PCMove(direction(key));
            
        // invalid key
        } else {
            continue;
        }
        
        
        clear();
        refresh();
        
        // displays user interface
        mvaddstr(0, 0, (d->print()).c_str());
        

        // check for win and death
        // if win
        if (g->win()) {
            clear();
            refresh();
            
            ostringstream ws;
            ws << "Congratulations! You won! You final score is ";
            ws << d->getScore() << endl;
            string winMessage = ws.str();
            mvaddstr(0, 0, winMessage.c_str());
            
            gameEnd = true;
        }
        
        // if die
        if (g->PCdied()) {
            clear();
            refresh();
    
            string pcDiedMessage = "You died!\n";
            mvaddstr(0, 0, pcDiedMessage.c_str());
            
            gameEnd = true;
        }
        
        if (gameEnd) {
            ostringstream ps;
            ps << "Do you want to play again?" << endl;
            ps << "If yes, enter 'n' to play a new game. ";
            ps << "If no, enter anything else to quit." << endl;
            string playAgainMessage = ps.str();
            mvaddstr(2, 0, playAgainMessage.c_str());
            
            key = getch();
            if (key == 'n') {
                clear();
                refresh();
                newGame(d, g);
                gameEnd = false;
                continue;
            } else {
                break;
            }
        }
    }
    
    endwin();
}
