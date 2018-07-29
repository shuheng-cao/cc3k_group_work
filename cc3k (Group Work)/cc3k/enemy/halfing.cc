#include "halfing.h"
#include <math.h>
using namespace std;


Halfing::Halfing(int x, int y, std::string name):
    Enemy(x, y, 100, 15, 20, name) {}


int Halfing::attackedBy(std::shared_ptr<Character> chr) {
    int missOrNot = rand() % 2;
    if (missOrNot) {
        int damage = ceil(100 / (100 + getDef()) * chr->getAtk());
        setHp(getHp() - damage);
        if (getHp() <= 0) {
            setState(CharacterState::DEAD);
            shared_ptr<PC> pc = dynamic_pointer_cast<PC>(chr);
            addDemiseGold(pc);
            notifyObservers();
        }
        return damage;
    } else {
        return 0;
    }
}


