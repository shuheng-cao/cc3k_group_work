#include "dwarf.h"
#include <math.h>

using namespace std;


Dwarf::Dwarf(int x, int y, std::string name): Enemy(x, y, 100, 20, 30, name) {}


int Dwarf::attackedBy(std::shared_ptr<Character> chr) {
    if (chr->getName() == "vampire") {
        chr->setHp(getHp() - 5);
    }
    int damage = ceil(100 / (100 + getDef()) * chr->getAtk());
    setHp(getHp() - damage);
    if (getHp() <= 0) {
        setState(CharacterState::DEAD);
        shared_ptr<PC> pc = dynamic_pointer_cast<PC>(chr);
        addDemiseGold(pc);
        notifyObservers();
    }
    return damage;
}



