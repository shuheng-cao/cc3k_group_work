#include "textdisplay.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// read in different files


// display content in the file
void TextDisplay::displayFile(string fileName) {
    ifstream myFile(fileName);
    string line;
    if (!myFile) {
        cout << "Not available file" << endl;
        exit(1);
    }
    while (!myFile.eof()) {
        getline(myFile, line);
        cout << line << endl;
    }
}


// update map (gridDisplay)
void TextDisplay::beUpdated(Grid* grid) {
    gridDisplay.clear();
    for (int row = 0; row < 25; ++row) {
        vector<char> aRow;
        for (int col = 0; col < 79; ++col) {
            CellType eachCellType = grid->getCellType(make_pair(row, col));
            if (eachCellType == CellType::VWALL) {
                aRow.emplace_back('|');
            } else if (eachCellType == CellType::HWALL) {
                aRow.emplace_back('-');
            } else if (eachCellType == CellType::PASSAGE) {
                aRow.emplace_back('#');
            } else if (eachCellType == CellType::STAIR) {
                aRow.emplace_back('\\');
            } else if (eachCellType == CellType::ABYSS) {
                aRow.emplace_back(' ');
                
            } else if (eachCellType == CellType::FLOOR) {
                aRow.emplace_back('.');
            } else if (eachCellType == CellType::DOORWAY) {
                aRow.emplace_back('+');
            } else if (eachCellType == CellType::GOLD) {
                aRow.emplace_back('G');
            } else if (eachCellType == CellType::PC) {
                aRow.emplace_back('@');
            } else if (eachCellType == CellType::POTION) {
                aRow.emplace_back('P');
            } else if (eachCellType == CellType::ENEMY) {
                string whatEnemy = grid->getEnemyType(make_pair(row, col));
                // - MARK: For debugging
//                cout << grid->getEnemyType(make_pair(row, col)) << endl;
                if (whatEnemy == "human") {
                    aRow.emplace_back('H');
                } else if (whatEnemy == "merchant") {
                    aRow.emplace_back('M');
                } else if (whatEnemy == "dwarf") {
                    aRow.emplace_back('W');
                } else if (whatEnemy == "elf") {
                    aRow.emplace_back('E');
                } else if (whatEnemy == "dragon") {
                    aRow.emplace_back('D');
                } else if (whatEnemy == "halfling") {
                    aRow.emplace_back('L');
                } else if (whatEnemy == "orc") {
                    aRow.emplace_back('O');
                }
            }
        }
        gridDisplay.emplace_back(aRow);
    }
}


void TextDisplay::notify(shared_ptr<Subject> whoFrom) {
    //notified when character attack
    // when potion is picked
    // when is moved
    
    shared_ptr<PC> pc = dynamic_pointer_cast<PC>(whoFrom);
    shared_ptr<Enemy> en = dynamic_pointer_cast<Enemy>(whoFrom);
    shared_ptr<Potion> pt = dynamic_pointer_cast<Potion>(whoFrom);
    shared_ptr<Treasure> tr = dynamic_pointer_cast<Treasure>(whoFrom);
    
    if (pc != nullptr){
        // if whofrom is a pc
        
        CharacterState chstate = pc->getState();
        // got what the pc has done
        // attack or move or missed or dead or invalid
        if (chstate == CharacterState::ATTACK) {
            // if the state is attacking
            // get who is fighting with
            string enemyName = pc->getTarget();
            int damageCaused = pc->getDamagesMade();
            
            
            
            gold = to_string(pc->getScore());
            // Action shows who is attacking and what damage
            pcAction = "";
            pcAction =  "PC deals "+ to_string(damageCaused)
                        + " damage to " + enemyName + ". ";
            if (pc->getTargetHp() > 0){
                pcAction = pcAction  + pc->getTarget() + " has "
                + to_string(pc->getTargetHp()) + " hp remaining. ";
            }
            
        } else if (chstate == CharacterState::MISS) {
            // if state is missed
            // Action show who miss the attack
//            action = "Action: ";
            pcAction = "";
            pcAction = pcAction + "You missed. ";
        }  else if (chstate == CharacterState::MOVE) {
            // if the state is moving  wait for grid to update
            pcAction = "";
            pcAction = "PC moved. ";
        } else if (chstate == CharacterState::INVALID) {
            pcAction = "";
            pcAction = "Invalid Move. ";
        }
    } else if (en != nullptr) {
        CharacterState chstate = en->getState();
        if (chstate == CharacterState::ATTACK) {
            enAction = "";
            string pcName = en->getTarget();
            int damageCaused = en->getDamagesMade();
            // set new hp
            hp = "HP: ";
            hp = hp + to_string(en->getTargetHp());
            
            enAction = enAction + en->getName() + " deals "
                + to_string(damageCaused) + " damage to PC. ";
            
            // Action shows who is attacking and what damage
        } else if (chstate == CharacterState::MISS) {
            // Action show who miss the attack
            enAction = "";
            enAction = enAction + en->getName() + " missed. ";
        }  else if (chstate == CharacterState::MOVE) {
            
        } else if (chstate == CharacterState::DEAD) {
            enAction = "";
            enAction = enAction + en->getName() + " is dead. ";
        }
    } else if(pt != nullptr) {
        // check which type of potion it is
        PotionType ptType = pt->getType();
        string which;
        switch (ptType) {
            case PotionType::PH:
                which = "PH";
                break;
            case PotionType::RH:
                which = "RH";
                break;
            case PotionType::WA:
                which = "WA";
                break;
            case PotionType::WD:
                which = "WD";
                break;
            case PotionType::BA:
                which = "BA";
                break;
            case PotionType::BD:
                which = "BD";
                break;
        }
        hp = "HP: ";
        hp = hp + to_string(pt->getUser()->getHp());
        atk = "Atk: ";
        atk = atk + to_string(pt->getUser()->getAtk());
        def = "Def: ";
        def = def + to_string(pt->getUser()->getDef());
        ptAction = "";
        ptAction = ptAction + "PC has used " + which + ". ";
        
    } else if(tr != nullptr) {
        // check what type the treasure is
        HoardType trType = tr->getType();
        string which;
        switch (trType) {
            case HoardType::SMALLHOARD:
                which = "small hoard";
                break;
            case HoardType::NORMALHOARD:
                which = "normal hoard";
                break;
            case HoardType::DRAGONHOARD:
                which = "dragon hoard";
                break;
            case HoardType::MERCHANTHOARD:
                which = "merchant hoard";
                break;
        }
        gold = "Gold: ";
        gold = gold + to_string(tr->getUser()->getScore());
        gdAction = "";
        gdAction = gdAction  + "PC has picked up " + which + ". ";
    }
}


// print grid and attribute display
string TextDisplay::print() {
    ostringstream ss;
    
    string gap =
    "                                                  ";
    
    for (auto &row : gridDisplay) {
        for (auto  &col : row) {
            ss << col ;
        }
        ss << endl;
    }
    
    ss << race << " " << gold;
    ss << gap << floor << endl;
    ss << hp << endl;
    ss << atk << endl;
    ss << def << endl;
    ss << action;
    ss << pcAction << enAction << ptAction << gdAction << exAction << endl;
    string s = ss.str();
    
    // clear action record for later
    pcAction = "";
    enAction = "";
    ptAction = "";
    gdAction = "";
    exAction = "";
    
    return s;
}


// Pretty pinter for double type
string prettyDoublePrint(double d) {
    int tmp = d * 10;
    return to_string(tmp / 10) + "." + to_string(tmp % 10);
}

// update PC information

void TextDisplay::raceAction(shared_ptr<PC> pc) {
    race = "Race: " + pc->getName();
    hp = "HP: " + to_string(pc->getHp());
    atk = "Atk: " + prettyDoublePrint(pc->getAtk());
    def = "Def: " + prettyDoublePrint(pc->getDef());
    gold = "Gold: " + to_string(pc->getScore());
}

// recieve invalid action from Grid

void TextDisplay::expAction(string what) {
    exAction = "";
    exAction = exAction + what;
}

int TextDisplay::getScore() {
    int score;
    istringstream (gold) >> score;
    return score;
}


// the rest haven't been used
///////////////////////////////////////////
void TextDisplay::floorAction(int floorNum) {
    floor = "Floor: ";
    floor = floor + to_string(floorNum);
}

void TextDisplay::pcattackAction(int damage, string enemyName) {
    action = action + "PC deals "+ to_string(damage) + " to " + enemyName;
}


void TextDisplay::enAttackAction(int damage, std::string enemyName) {
    
    action = action + enemyName + " deals " + to_string(damage) + " to PC";
}


void TextDisplay::enHpAction(int enHp, string enemyName) {
    action = action + enemyName + " has "+ to_string(enHp) + " hp remaining";
}


void TextDisplay::potionAction(PotionType pType) {
    string potion = "";
    switch (pType) {
        case PotionType::PH:
            potion = "PH";
            break;
        case PotionType::RH:
            potion = "RH";
            break;
        case PotionType::WA:
            potion = "WA";
            break;
        case PotionType::WD:
            potion = "WD";
            break;
        case PotionType::BA:
            potion = "BA";
            break;
        case PotionType::BD:
            potion = "BD";
            break;
    }
    action = "PC has used " + potion;
}


void TextDisplay::goldAction(HoardType gType) {
    string gold = "";
    switch (gType) {
        case HoardType::MERCHANTHOARD:
            gold = "merchant's gold";
            break;
        case HoardType::SMALLHOARD:
            gold = "small gold";
            break;
        case HoardType::NORMALHOARD:
            gold = "normal gold";
            break;
        case HoardType::DRAGONHOARD:
            gold = "dragon's gold";
            break;
    }
    action = "PC has picked up " + gold;
}


void TextDisplay::missAction(string who) {
    action = who + " missed attack";
}



