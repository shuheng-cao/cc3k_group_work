#include <math.h>
#include "dragon_hoard.h"


DragonHoard::DragonHoard(int x, int y): Treasure{x, y, 6} {}


// make the dragon hoard free to pick
void DragonHoard::freePick() {
    canPick = true;
}

bool DragonHoard::canBePicked() {
    return canPick;
}

// if it is picked by chr
void DragonHoard::pickedBy(std::shared_ptr<PC> chr) {
//    // if can not pick
//    if (!canPick) {
//        return;
//    }
    setUser(chr);
    // if can pick
    chr->addScore(floor(chr->getGFactor() * value));
    
    notifyObservers();
}
