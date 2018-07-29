#include "ph.h"


PH::PH(int x, int y): Potion{x, y, PotionType::PH} {}


// uses potion - Poison Health
void PH::usePotion(std::shared_ptr<PC> chr) {
    // loses up to 10 HP for most races (can not fall below 0 HP)
    chr->setHp(chr->getHp() - (10 * chr->getPFactor()));
    setUser(chr);
    notifyObservers();
}
