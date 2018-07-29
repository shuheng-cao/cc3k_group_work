#ifndef __DRAGON_HOARD_H__
#define __DRAGON_HOARD_H__
#include "treasure.h"

class DragonHoard final: public Treasure {
    const int value = 6;
    bool canPick = false;
    
public:
    DragonHoard(int x, int y);
    
    // make the dragon hoard free to pick
    void freePick();
    bool canBePicked();
    
    // if it is picked by chr
    void pickedBy(std::shared_ptr<PC> chr) override;
};
#endif
