#include "orc.h"

Orc::Orc(int x, int y, std::string name): Enemy(x, y, 180, 30, 25, name) {}


int Orc::attack(std::shared_ptr<Character> chr) {
    double multiplier = 1.0;
    if (chr->getName() == "goblin") {
        multiplier = 1.5;
    }
    int missOrNot = rand() % 2;
    if (missOrNot) {
        // Successful attack
        // Get a backup for my attack
        int atkBackup = getAtk();
        setAtk(static_cast<int>(atkBackup * multiplier));
        int causedDamage = chr->attackedBy(std::shared_ptr<Orc>
                                           (this, [](Orc*){}));
        // reset atk back to origin
        setAtk(atkBackup);
        setState(CharacterState::ATTACK);
        setDamagesMade(causedDamage);
        notifyObservers();
        return causedDamage;
    } else {
        // Unsuccessful attack
        setState(CharacterState::MISS);
        notifyObservers();
        return 0;
    }
    // Of no use
    return -1;
}
