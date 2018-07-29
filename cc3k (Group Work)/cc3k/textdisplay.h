#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "grid.h"
#include <string>
#include <vector>
#include "observer.h"
#include "character.h"
#include "type.h"
#include "potion/potion.h"
#include "treasure/treasure.h"
#include "enemy/enemy.h"
#include "pc/pc.h"
#include <string>
#include <sstream>
#include <memory>


class TextDisplay: public Observer {
    std::vector<std::vector<char>> gridDisplay;
    std::string race = "Race: ";
    std::string gold = "Gold: ";
    std::string floor = "Floor: ";
    std::string hp = "HP: ";
    std::string atk = "Atk: ";
    std::string def = "Def: ";
    std::string action = "Action: ";
    std::string pcAction = "";
    std::string enAction = "";
    std::string ptAction = "";
    std::string gdAction = "";
    std::string exAction = "";
public:
    void beUpdated(Grid* grid);
    void displayFile(std::string fileName);
    void notify(std::shared_ptr<Subject> whoFrom) override;
    void raceAction(std::shared_ptr<PC> pc);
    void floorAction(int floorNum);
    void pcattackAction(int damage, std::string enemyName);
    void enAttackAction(int damage, std::string enemyName);
    void enHpAction(int enHp, std::string enemyName);
    void potionAction(PotionType pType);
    void goldAction(HoardType gType);
    void missAction(std::string who);
    void expAction(std::string what);
    int getScore();
    std::string print();
};

#endif 
