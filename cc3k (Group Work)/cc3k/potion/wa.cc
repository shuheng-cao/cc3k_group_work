#include "wa.h"


WA::WA(int x, int y): Potion{x, y, PotionType::WA} {}


// uses potion - Wound Atk
void WA::usePotion(std::shared_ptr<PC> chr) {
    // decreases Atk by 5
    chr->setAtk(chr->getAtk() - (5 * chr->getPFactor()));
    setUser(chr);
    notifyObservers();
}
