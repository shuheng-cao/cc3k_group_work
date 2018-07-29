#ifndef __GRID_H__
#define __GRID_H__

#include "subject.h"
#include "observer.h"
#include "type.h"
#include "textdisplay.h"
#include <memory>

class Character;
class Potion;
class Treasure;
class TextDisplay;

class Grid: public Observer {
    struct Mysubjects;
//  My subjects include PC, enemies, golds and potions
    std::shared_ptr<Mysubjects> mySubjects;
    std::shared_ptr<TextDisplay> display;
    int floor = 1;
    bool frozen = false;
    bool willMerchantAttak = false;
    std::string myFileName;
//  private helpers:
    std::pair<int, int> randomSpawn();
//  private helper for initGame
    void readInMap(Grid* myGrid, std::string fileName);
    void setCellType(std::pair<int, int> myPair, CellType myCellType);
//  private helper for enemies to move or attack
    bool withInOneGrid(std::pair<int, int>, std::pair<int, int>);
    void enemiesTurn();
//  private helper for getEnemyName()
    std::shared_ptr<Character> getEnemy(std::pair<int, int> myPair);
    std::shared_ptr<Treasure> getTreasure(std::pair<int, int> myPair);
    std::shared_ptr<Potion> getPotion(std::pair<int, int> myPair);
//  private helper to motify the Grid
    void resetCell(std::pair<int, int> myPosn, CellType newType);
public:
    Grid();
    // We do all types of initialization in initGame() using
    // the private helper randomSpawn()
    void setDisplay(std::shared_ptr<TextDisplay> dis);
    void initGame(std::string fileName, PCType myPC);
    void initGrid(std::string fileName, PCType myPC);
    void toggleFrozen();
    bool win(); // Do we really need this?
    bool PCdied();
    CellType getCellType(std::pair<int, int> myPair);
    std::string getEnemyType(std::pair<int, int> myPair);
    void update();
    // Go to next floor
    void nextFloor();
    // new method
    void updatePCRace();
    void updateFloor();
    // Actions from controller
    // Should automatically call enemies move
    void PCMove(Direction dir);
    void PCAttack(Direction dir);
    void PCPickUp(Direction dir);
    void notify(std::shared_ptr<Subject> whoFrom) override;
};

#endif

