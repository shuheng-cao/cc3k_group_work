#include "vampire.h"
using namespace std;


Vampire::Vampire(int x, int y, int hp, double atk, double def, string name):
PC{x, y, hp , atk, def, name} {
    
}


int Vampire::attack(shared_ptr<Character> chr) {
    setHp(getHp() + 5);
    // - MARK: add by Shuheng, need double check
    return chr->attackedBy(shared_ptr<Character>(this, [](Character*){}));
}
