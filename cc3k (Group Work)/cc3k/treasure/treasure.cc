#include <math.h>
#include <cstdlib>
#include "treasure.h"


Treasure::Treasure(int x, int y, int val): Item{x, y}, value{val} {}


// if it is picked by chr
void Treasure::pickedBy(std::shared_ptr<PC> chr) {
    chr->addScore(floor(chr->getGFactor() * value));
    setUser(chr);
    notifyObservers();
}


// randomly generates normal or small pile of gold
//and immediately adds to players' total.
// (Only call upon the qualified enemies' demise.)
void Treasure::addDemiseGold(std::shared_ptr<PC> chr) {
    int pile = 0;
    pile = rand() % 2 + 1;   // 1 - small pile, 2 - normal pile
    
    // immediately adds to players' total score
    chr->addScore(floor((chr->getGFactor() * pile) + chr->getSteal()));
}


// gets type of treasure
HoardType Treasure::getType() {
    if (value == 6) {
        return HoardType::DRAGONHOARD;
    } else if (value == 4) {
        return HoardType::MERCHANTHOARD;
    } else if (value == 2) {
        return HoardType::NORMALHOARD;
    } else {
        return HoardType::SMALLHOARD;
    }
}
