#include "elf.h"
#include <memory>


Elf::Elf(int x, int y, std::string name): Enemy(x, y, 140, 30, 10, name) {}


int Elf::attack(std::shared_ptr<Character> chr) {
    int causedDamage = 0;
    int howManyTimes = 0;
    (chr->getName() == "drow")? howManyTimes = 1: howManyTimes = 2;
    for (int i = 0; i < howManyTimes; ++i) {
        int missOrNot = rand() % 2;
        if (missOrNot) {
            
            // Successful attack
            int damage = chr->attackedBy(std::shared_ptr<Character>(this, [](Character*){}));
            causedDamage += damage;
            setState(CharacterState::ATTACK);
            setDamagesMade(damage);
            notifyObservers();
        } else {
            // Unsuccessful attack
            setState(CharacterState::MISS);
            notifyObservers();
        }
    }
    return causedDamage;
}


