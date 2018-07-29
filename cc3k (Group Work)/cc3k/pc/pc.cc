#include "pc.h"
#include <math.h>
using namespace std;


PC::PC(int x, int y, int hp, double atk, double def, string name):
Character{x, y, hp, atk, def, name}  {
    
}


void PC::move(Direction dir) {
//    find the destination it's going to move
    pair <int, int> destination = nextCell(dir);
    CellType cellType = myGrid->getCellType(destination);
    if (cellType == CellType::FLOOR || cellType == CellType::PASSAGE ||
        cellType == CellType::DOORWAY || cellType == CellType::STAIR
        || cellType == CellType::GOLD) {
        
        if (getName() == "troll") {
            setHp(getHp() + 5);
        }
        setWhereFrom(dir);
        setState(CharacterState::MOVE);
        notifyObservers();
        
        this->setY(destination.second);
        this->setX(destination.first);
        
        
        //notifyObservers();
    } else if (cellType == CellType::STAIR){
        reset();
        this->setY(destination.second);
        this->setX(destination.first);
        notifyObservers();
    } else {
        setState(CharacterState::INVALID);
        notifyObservers();
    }
}


int PC::getScore() {
    return myScore;
}


int PC::getSteal() {
    return slainSteal;
}


int PC::getGFactor(){
    return goldFactor;
}


int PC::getPFactor() {
    return potionFactor;
}


void PC::addScore(int n) {
    myScore+= n;
}


// pc uses potion
// call potions function to determine who uses it
void PC::consumePotion(shared_ptr<Potion> p) {
    p->usePotion(shared_ptr<PC>(this, [](PC*){}));
}


void PC::setGFactor(double gf) {
    goldFactor = gf;
}


void PC::setPFactor(double pf) {
    potionFactor = pf;
}


void PC::setSteal(int ss){
    slainSteal = ss;
}


PC::~PC() {
    
}
