#include "bd.h"


BD::BD(int x, int y): Potion{x, y, PotionType::BD} {}


// uses potion - Boost Def
void BD::usePotion(std::shared_ptr<PC> chr) {
    // increases Def by 5
    chr->setDef(chr->getDef() + (5 * chr->getPFactor()));
    setUser(chr);
    notifyObservers();
}
