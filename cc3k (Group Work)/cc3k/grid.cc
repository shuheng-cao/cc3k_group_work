#include "grid.h"
#include <string>
#include <fstream>
#include <vector>
#include "character.h"
#include "enemy/dragon.h"
#include "treasure/treasure.h"
#include "factory/pc_factory.h"
#include "factory/enemy_factory.h"
#include "factory/potion_factory.h"
#include "factory/treasure_factory.h"

#include <iostream>


using namespace std;

const int HEIGHT = 25;
const int WIDTH = 79;


// Generate randomly posn for items and characters
std::pair<int, int> Grid::randomSpawn() {
    pair<int, int> tmpPair;
    do {
        int randx = rand() % HEIGHT;
        int randy = rand() % WIDTH;
        tmpPair = make_pair(randx, randy);
    } while (getCellType(tmpPair) != CellType::FLOOR);
    return tmpPair;
}


// Hidden struct, using PIMPL
struct Grid::Mysubjects {
    vector<vector<CellType>> emptymap;
    vector<vector<CellType>> map;
    vector<shared_ptr<Subject>> enemies;
    shared_ptr<Subject> PC;
    vector<shared_ptr<Subject>> golds;
    vector<shared_ptr<Subject>> potions;
};


// Constructor
Grid::Grid(): mySubjects {make_unique<struct Mysubjects>()}, display {make_shared<TextDisplay>()} {}
void Grid::setDisplay(std::shared_ptr<TextDisplay> dis) {
    display = dis;
}


// read in from the .txt to form an empty grid
void Grid::readInMap(Grid* myGrid, string fileName) {
    // Clear up the old memory
    myGrid->mySubjects->map.clear();
    myGrid->mySubjects->map.clear();
    myGrid->mySubjects->enemies.clear();
    myGrid->mySubjects->golds.clear();
    myGrid->mySubjects->potions.clear();
    
    // Read in from fileName.txt
    ifstream floorFile{fileName};
    string oneLine;
    
    
    for (int i = 0; i < HEIGHT; ++i) {
        getline(floorFile, oneLine);
        vector<CellType> tmpCellVec;
        for (int j = 0; j < WIDTH; ++j) {
            char tmpChar = oneLine[j];
            CellType tmpCell;
            switch (tmpChar) {
                case '|':
                    tmpCell = CellType::VWALL;
                    break;
                case '-':
                    tmpCell = CellType::HWALL;
                    break;
                case '+':
                    tmpCell = CellType::DOORWAY;
                    break;
                case '#':
                    tmpCell = CellType::PASSAGE;
                    break;
                case ' ':
                    tmpCell = CellType::ABYSS;
                    break;
                default:
                    tmpCell = CellType::FLOOR;
                    break;
            }
            tmpCellVec.emplace_back(tmpCell);
        }
        myGrid->mySubjects->map.emplace_back(tmpCellVec);
        myGrid->mySubjects->emptymap.emplace_back(tmpCellVec);
    }
}


void Grid::initGame(string fileName, PCType myPC) {
    floor = 1;
    frozen = false;
    willMerchantAttak = false;
    initGrid(fileName, myPC);
}


void Grid::initGrid(string fileName, PCType myPC) {
    myFileName = fileName;
    readInMap(this, fileName);
   
    pair<int, int> randomPair = randomSpawn();
    int randx = randomPair.first;
    int randy = randomPair.second;
    
    // 1. Set up posn for PC
    PCFactory myPCFactory;
    mySubjects->PC = myPCFactory.create(randx, randy, myPC);
    setCellType(randomPair, CellType::PC);
    
    // Obervers for PC
    shared_ptr<PC> tmpPC = dynamic_pointer_cast<PC>(mySubjects->PC);
    tmpPC->attach(shared_ptr<Observer>(this, [](Observer*){}));
    tmpPC->attach(display);
    try{
        tmpPC->setMyGrid(shared_ptr<Grid>(this, [](Observer*){}));
    } catch (invalid_argument &e) {
        cout << e.what() << endl;
    }
    
    //  2. Set up posn for StairWay
    bool sameChamber = true;
    while (sameChamber) {
        randomPair = randomSpawn(); // update my pair
        if (abs(randomPair.first - randx) >= 10 && abs(randomPair.second - randy) >= 20) {
            sameChamber = false;
        }
    }
    setCellType(randomPair, CellType::STAIR);
    
    
    // 3. Set up posn for potions
    PotionFactory myPotionFactory;
    for (int i = 0; i < 10; ++i) {
        randomPair = randomSpawn();
        randx = randomPair.first;
        randy = randomPair.second;
        shared_ptr<Potion> tmpPotion
        = myPotionFactory.create(randx, randy);
        mySubjects->potions.emplace_back(tmpPotion);
        setCellType(randomPair, CellType::POTION);
        // Observers for Potions
        tmpPotion->attach(shared_ptr<Observer>(this, [](Observer*){}));
        tmpPotion->attach(display);
    }
    
    // 4. Set up posn for golds
    TreasureFactory myTreasureFactory;
    for (int i = 0; i < 10; ++i) {
        randomPair = randomSpawn();
        randx = randomPair.first;
        randy = randomPair.second;
        shared_ptr<Treasure> tmpTreasure
        = myTreasureFactory.create(randx, randy);
        mySubjects->golds.emplace_back(tmpTreasure);
        setCellType(randomPair, CellType::GOLD);
        // Set up Observers for golds
        tmpTreasure->attach(shared_ptr<Observer>(this, [](Observer*){}));
        tmpTreasure->attach(display);
        // Check whether or not we need to place a dragon
        if (tmpTreasure->getType() == HoardType::DRAGONHOARD) {
            auto myTreasure = dynamic_pointer_cast<DragonHoard>(tmpTreasure);
            bool haveSetDragon = false;
            for (int m = -1; m <= 1 && !haveSetDragon; ++m) {
                for (int n = -1; n <= 1 && !haveSetDragon; ++n) {
                    if (getCellType(make_pair(randx+m, randy+n))
                        == CellType::FLOOR) {
                        setCellType(make_pair(randx+m, randy+n),
                                    CellType::ENEMY);
                        shared_ptr<Dragon> myDragon = make_shared<Dragon>(dynamic_pointer_cast <DragonHoard>(tmpTreasure), randx+m, randy+n);
                        myDragon->setMyHoard(myTreasure);
                        mySubjects->enemies.emplace_back(myDragon);
                        // Set up Obervers for Dragon
                        myDragon->attach(shared_ptr<Observer>
                                         (this, [](Observer*){}));
                        myDragon->attach(display);
                        
                        haveSetDragon = true;
                        // - MARK: for debugging
                        //cout << myDragon->getName() << ": " << randx
                        // << ", " << randy << endl;
                    }
                }
            }
        }
    }
     
    // 5. Set up enemies
    EnemyFactory myEnemyFactory;
    for (int i = 0; i < 20; ++i) {
        randomPair = randomSpawn();
        randx = randomPair.first;
        randy = randomPair.second;
        shared_ptr<Enemy> tmpEnemy
        = myEnemyFactory.create(randx, randy);
        
        // - MARK: For debugging
//        cout << tmpEnemy->getName() << ": " << randx << ", " << randy << endl;
        
        
        setCellType(randomPair, CellType::ENEMY);
        // Set up Obervers for Enemy
/*        shared_ptr<Enemy>someEnemy = dynamic_pointer_cast<Enemy>()
        someEnemy->attach(shared_ptr<Observer>(this, [](Observer*){}));
        someEnemy->attach(display); */
        tmpEnemy->attach(shared_ptr<Observer>(this, [](Observer*){}));
        tmpEnemy->attach(display);
        try {
            tmpEnemy->setMyGrid(shared_ptr<Grid>(this, [](Observer*){}));
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
        }
        
        mySubjects->enemies.emplace_back(tmpEnemy);
        
    }
    // - MARK: End of intilization
//    cout << "End of setting enemy" << endl;
    update();
    updatePCRace();
    updateFloor();
}


// change enmies's frozen status
void Grid::toggleFrozen() {
    frozen = !frozen;
}


// tell if PC wins the game
bool Grid::win() {
    return (floor > 5);
}


// tell if PC died
bool Grid::PCdied() {
    shared_ptr<PC> myPC = dynamic_pointer_cast<PC>(mySubjects->PC);
    return (myPC->getHp() <= 0);
}


CellType Grid::getCellType(std::pair<int, int> myPair) {
    return mySubjects->map[myPair.first][myPair.second];
}


shared_ptr<Character> Grid::getEnemy(std::pair<int, int> myPair) {
    for (auto it: mySubjects->enemies) {
        if (myPair == it->getPosn()) {
            try {
                shared_ptr<Character> downCasting
                = dynamic_pointer_cast<Character>(it);
                return downCasting;
            } catch (...) {
                return nullptr;
            }
        }
    }
    return nullptr;
}


shared_ptr<Treasure> Grid::getTreasure(std::pair<int, int> myPair) {
    for (auto it: mySubjects->golds) {
        if (myPair == it->getPosn()) {
            try {
                shared_ptr<Treasure> downCasting
                = dynamic_pointer_cast<Treasure>(it);
                return downCasting;
            } catch (...) {
                return nullptr;
            }
        }
    }
    return nullptr;
}


shared_ptr<Potion> Grid::getPotion(std::pair<int, int> myPair) {
    for (auto it: mySubjects->potions) {
        if (myPair == it->getPosn()) {
            try {
                shared_ptr<Potion> downCasting
                = dynamic_pointer_cast<Potion>(it);
                return downCasting;
            } catch (...) {
                return nullptr;
            }
        }
    }
    return nullptr;
}


std::string Grid::getEnemyType(std::pair<int, int> myPair) {
    if (getEnemy(myPair)) {
        return getEnemy(myPair)->getName();
    }
    return "ERROR";
}


void Grid::setCellType(std::pair<int, int> myPair, CellType myCellType) {
    mySubjects->map[myPair.first][myPair.second] = myCellType;
}


void Grid::update() {
    display->beUpdated(this);
}


void Grid::updatePCRace() {
    shared_ptr<PC> myPC = dynamic_pointer_cast<PC>(mySubjects->PC);
    display->raceAction(myPC);
}


void Grid::updateFloor() {
    display->floorAction(floor);
}


// Helper for enemiesTurn helper
bool Grid::withInOneGrid(std::pair<int, int> posnOne,
                         std::pair<int, int> posnTwo) {
    return abs(posnOne.first - posnTwo.first) < 2
    && abs(posnOne.second - posnTwo.second) < 2;
}


void Grid::enemiesTurn() {
    shared_ptr<Character> myPC =
        dynamic_pointer_cast<Character>(mySubjects->PC);
    for (auto &it: mySubjects->enemies) {
        shared_ptr<Enemy> currentEnemy = dynamic_pointer_cast<Enemy>(it);
        shared_ptr<Dragon> myDragon =
        dynamic_pointer_cast<Dragon>(currentEnemy);
        if (myDragon != nullptr) {
            shared_ptr<DragonHoard> myHoard = myDragon->getMyHoard();
            if (withInOneGrid(myPC->getPosn(), myHoard->getPosn())) {
                currentEnemy->attack(myPC);
            }
        } else {
            shared_ptr<Merchant> myMerchant =
            dynamic_pointer_cast<Merchant>(currentEnemy);
            if (withInOneGrid(myPC->getPosn(), currentEnemy->getPosn())) {
                if (myMerchant != nullptr && !willMerchantAttak) {
                    if (!frozen) {
                        myMerchant->move(Direction::N);
                    }
                    continue;
                }
                currentEnemy->attack(myPC);
            } else {
                if (!frozen) {
                    currentEnemy->move(Direction::N);
                }
            }
        }
    }
}


void Grid::nextFloor() {
    shared_ptr<PC> myOldPC = dynamic_pointer_cast<PC>(mySubjects->PC);
    myOldPC->reset();
    initGrid(myFileName, PCType::SHADE);
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (mySubjects->map[i][j] == CellType::PC) {
                myOldPC->setX(i);
                myOldPC->setY(j);
            }
        }
    }
    mySubjects->PC = myOldPC;
    floor++;
    updateFloor();
}


// - MARK: should add exception here
// Maybe need to consider when to pick up gold
void Grid::PCMove(Direction dir) {
    shared_ptr<PC> myPC = dynamic_pointer_cast<PC>(mySubjects->PC);
    pair<int, int> oldCell = myPC->getPosn();
    pair<int, int> nextCell = myPC->nextCell(dir);
    if (getCellType(nextCell) == CellType::GOLD) {
        shared_ptr<DragonHoard> tryHoard = dynamic_pointer_cast<DragonHoard>(getTreasure(nextCell));
        if (tryHoard != nullptr) {
            if (tryHoard->canBePicked()) {
                tryHoard->pickedBy(myPC);
                updatePCRace();
            } else {
                display->expAction
                ("Can't pick up dragon hoard before kill the dragon. ");
                enemiesTurn();
                updatePCRace();
                update();
                return;
            }
        } else {
            getTreasure(nextCell)->pickedBy(myPC);
            updatePCRace();
        }
    } else if (getCellType(nextCell) == CellType::STAIR) {
        nextFloor();
    }
    myPC->move(dir);
    // reset the previous cell
    if(myPC->getState() == CharacterState::MOVE) {
        resetCell(oldCell, mySubjects->emptymap[oldCell.first][oldCell.second]);
    }
    enemiesTurn();
    updatePCRace();
    update();
}


// - MARK: should add exception here
void Grid::PCAttack(Direction dir) {
    shared_ptr<Character> myPC =
    dynamic_pointer_cast<Character>(mySubjects->PC);
    pair<int, int> nextCell = myPC->nextCell(dir);
    if (getCellType(nextCell) == CellType::ENEMY) {
        auto tmpEnemy = getEnemy(myPC->nextCell(dir));
        // Toggle the merchant attack
        shared_ptr<Merchant> tryMerchant =
        dynamic_pointer_cast<Merchant>(tmpEnemy);
        if (tryMerchant != nullptr && !willMerchantAttak) {
            willMerchantAttak = true;
        }
        myPC->attack(tmpEnemy);
        if (tmpEnemy->getState() == CharacterState::DEAD) {
            shared_ptr<Dragon> tryDragon =
            dynamic_pointer_cast<Dragon>(tmpEnemy);
            if (tryDragon != nullptr) {
                tryDragon->getMyHoard()->freePick();
            }
            // Reset all enemies
            vector<shared_ptr<Subject>> newEnemies;
            for (auto it: mySubjects->enemies) {
                if (it == tmpEnemy) continue;
                newEnemies.emplace_back(it);
            }
            mySubjects->enemies = newEnemies;
        }
    } else {
        display->expAction("Fail to attack: no enemy in the direction.");
    }
    enemiesTurn();
    updatePCRace();
    update();
}


// - MARK: should add exception here
void Grid::PCPickUp(Direction dir) {
    shared_ptr<PC> myPC = dynamic_pointer_cast<PC>(mySubjects->PC);
    pair<int, int> nextCell = myPC->nextCell(dir);
    if (getCellType(nextCell) == CellType::POTION) {
        myPC->consumePotion(getPotion(myPC->nextCell(dir)));
        resetCell(myPC->nextCell(dir), CellType::FLOOR);
        update();
    } else {
        display->expAction("Fail to pick up: no potion in the direction.");
    }
    enemiesTurn();
    updatePCRace();
    update();
}


void Grid::resetCell(std::pair<int, int> myPosn, CellType newType) {
    mySubjects->map[myPosn.first][myPosn.second] = newType;
}


void Grid::notify(std::shared_ptr<Subject> whoFrom) {
    // Try dynamic casting in order to find the exact type
    shared_ptr<Treasure> tryTreasure = dynamic_pointer_cast<Treasure>(whoFrom);
    shared_ptr<Potion> tryPotion = dynamic_pointer_cast<Potion>(whoFrom);
    shared_ptr<PC> tryPC = dynamic_pointer_cast<PC>(whoFrom);
    shared_ptr<Enemy> tryEnemy = dynamic_pointer_cast<Enemy>(whoFrom);
    if (tryTreasure != nullptr) {
        resetCell(tryTreasure->getPosn(), CellType::FLOOR);
    }
    else if (tryPotion != nullptr) {
        resetCell(tryPotion->getPosn(), CellType::FLOOR);
    }
    else if (tryEnemy != nullptr) {
        if (tryEnemy->getState() == CharacterState::DEAD) {
            resetCell(tryEnemy->getPosn(), CellType::FLOOR);
            if (tryEnemy->getName() == "human") {
                // Create two piles of gold
                for (int i = 0; i < 2; ++i) {
                    bool success = false;
                    while (!success) {
                        int randx = tryEnemy->getX() + rand() % 3 - 1;
                        int randy = tryEnemy->getY() + rand() % 3 - 1;
                        pair<int, int> randPair = make_pair(randx, randy);
                        if (getCellType(randPair) == CellType ::FLOOR) {
                            resetCell(randPair, CellType::GOLD);
                            shared_ptr<Subject> addGold =
                                make_shared<NormalHoard>(randx, randy);
                            mySubjects->golds.emplace_back(addGold);
                            addGold->attach(shared_ptr<Observer>(this, [](Observer*){}));
                            addGold->attach(display);
                            success = true;
                        }
                    }
                }
            } else if (tryEnemy->getName() == "merchant") {
                bool success = false;
                while (!success) {
                    int randx = tryEnemy->getX() + rand() % 3 - 1;
                    int randy = tryEnemy->getY() + rand() % 3 - 1;
                    pair<int, int> randPair = make_pair(randx, randy);
                    if (getCellType(randPair) == CellType ::FLOOR) {
                        resetCell(randPair, CellType::GOLD);
                        shared_ptr<Subject> addGold =
                            make_shared<MerchantHoard>(randx, randy);
                        mySubjects->golds.emplace_back(addGold);
                        addGold->attach(shared_ptr<Observer>(this, [](Observer*){}));
                        addGold->attach(display);
                        success = true;
                    }
                }
            }
        } else if (tryEnemy->getState() == CharacterState::MOVE) {
            resetCell(tryEnemy->getPosn(), CellType::FLOOR);
            Direction dir = tryEnemy->getWhereFrom();
            resetCell(tryEnemy->nextCell(dir), CellType::ENEMY);
        }
        // If the state is attack, miss or any other thing, it's
        //   textdisplay's responsibility to deal with them
    }
    else if (tryPC != nullptr) {
        // If PC die, we will use another notify
        if (tryPC->getState() == CharacterState::MOVE) {
            resetCell(tryPC->getPosn(), CellType::FLOOR);
            Direction dir = tryPC->getWhereFrom();
            resetCell(tryPC->nextCell(dir), CellType::PC);
        }
    }
}


