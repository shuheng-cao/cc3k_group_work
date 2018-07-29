#include <iostream>
#include "textdisplay.h"
#include "grid.h"
#include "type.h"
#include "normal_controller.h"
using namespace std;


// start a new game
void startNewGame(shared_ptr<TextDisplay> d, shared_ptr<Grid> g) {
    char race;
    PCType type;

    // select pc character race
    d->displayFile("selectPC.txt");
    cin >> race;
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
        } else {
            cout << "Invaild choice. Please choose again." << endl;
            cin >> race;
        }
    }

    // initilize game
    g->initGame("emptyfloor.txt", type);
    cout << d->print();
}


// transfer string dir into Direction type
Direction convertDirection(string dir) {
    if (dir == "nw") {
        return Direction::NW;
    } else if (dir == "ne") {
        return Direction::NE;
    } else if (dir == "sw") {
        return Direction::SW;
    } else if (dir == "se") {
        return Direction::SE;
    } else if (dir == "n") {
        return Direction::N;
    } else if (dir == "w") {
        return Direction::W;
    } else if (dir == "e") {
        return Direction::E;
    } else {
        return Direction::S;
    }
}


// play the game in normal version
void NormalController::play() {
    shared_ptr<Grid> g = make_shared<Grid>();
    shared_ptr<TextDisplay> d = make_shared<TextDisplay>();
    g->setDisplay(d);
    
    string cmd;
    bool gameEnd = false;
    
    // leave space between the new and the old
    for (int i = 0; i < 30; i++) {
        cout << endl;
    }
    
    cout << "In the normal version, you will play using commands." << endl;
    cout << endl;
    startNewGame(d, g);
    
    while (true) {
        cin >> cmd;
        string dir;
        
        // uses the potion in the direction
        if (cmd == "u") {
            cin >> dir;
            g->PCPickUp(convertDirection(dir));
        
        // attacks the enemy in the direction
        } else if (cmd == "a") {
            cin >> dir;
            g->PCAttack(convertDirection(dir));

        // stops enemies from moving until this key is pressed again
        } else if (cmd == "f") {
            g->toggleFrozen();
                
        // restarts the game
        } else if (cmd == "r") {
            // leave space between the new and the old
            for (int i = 0; i < 30; i++) {
                cout << endl;
            }
            
            startNewGame(d, g);
            continue;
                
        // quits the game
        } else if (cmd == "q") {
            break;
            
        // moves in the direction entered
        } else if ((cmd == "nw") || (cmd == "ne") || (cmd == "sw") ||
                   (cmd == "se") || (cmd == "n") || (cmd == "e") ||
                   (cmd == "w") || (cmd == "s")) {
            g->PCMove(convertDirection(cmd));
        
        // invalid command
        } else {
            cout << "Invalid command. Please enter a correct one." << endl;
            continue;
        }
        
        
        // leave space between the new and the old
        for (int i = 0; i < 30; i++) {
            cout << endl;
        }
        
        // displays user interface
        cout << d->print();
        
        
        // check for win and death
        // if win
        if (g->win()) {
            
            // leave space between the new and the old
            for (int i = 0; i < 30; i++) {
                cout << endl;
            }
            
            cout << "Congratulations! You won! You final score is "
            << d->getScore() << endl;
            gameEnd = true;
            
        }
        
        // if die
        if (g->PCdied()) {
            
            // leave space between the new and the old
            for (int i = 0; i < 30; i++) {
                cout << endl;
            }
            
            cout << "You died!" << endl;
            gameEnd = true;
        }
        
        if (gameEnd) {
            cout << endl << "Do you want to play again?" << endl;
            cout << "If yes, enter 'n' to play a new game. ";
            cout << "If no, enter anything else to quit." << endl;
            
            cin >> cmd;
            if (cmd == "n") {
                startNewGame(d, g);
                gameEnd = false;
                continue;
            } else {
                break;
            }
        }
    }
}
