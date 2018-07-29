#include "merchant.h"
#include <math.h>


Merchant::Merchant(int x, int y, std::string name):
Enemy{x, y, 30, 70, 5, name} {}

int Merchant::attackedBy(std::shared_ptr<Character> chr) {
    int damage = ceil(100 / (100 + getDef()) * chr->getAtk());
    setHp(getHp() - damage);
    if (getHp() <= 0) {
        setState(CharacterState::DEAD);
        std::shared_ptr<PC> pc = std::dynamic_pointer_cast<PC>(chr);
        addDemiseGold(pc);
        notifyObservers();
    }
    return damage;
}


