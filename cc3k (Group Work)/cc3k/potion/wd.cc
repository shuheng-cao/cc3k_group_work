#include "wd.h"


WD::WD(int x, int y): Potion{x, y, PotionType::WD} {}


// uses potion - Wound Def
void WD::usePotion(std::shared_ptr<PC> chr) {
    // decreases Def by 5
    chr->setDef(chr->getDef() - (5 * chr->getPFactor()));
    setUser(chr);
    notifyObservers();
}
