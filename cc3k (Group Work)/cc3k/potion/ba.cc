#include "ba.h"


BA::BA(int x, int y): Potion{x, y, PotionType::BA} {}


// uses potion - Boost Atk
void BA::usePotion(std::shared_ptr<PC> chr) {
    // increases Atk by 5
    chr->setAtk(chr->getAtk() + (5 * chr->getPFactor()));
    setUser(chr);
    notifyObservers();
}
