#include "rh.h"


RH::RH(int x, int y): Potion{x, y, PotionType::RH} {}


// uses potion - Restore Health
void RH::usePotion(std::shared_ptr<PC> chr) {
    // restore up to 10 HP (can not exceed maximum for the race)
    chr->setHp(chr->getHp() - (10 * chr->getPFactor()));
    setUser(chr);
    notifyObservers();
}
