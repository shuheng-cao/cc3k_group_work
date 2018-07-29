#ifndef __POTION_H__
#define __POTION_H__
#include "../item.h"
#include "../type.h"
#include "../pc/pc.h"

class PC;

class Potion: public Item {
    PotionType type;
    
public:
    Potion(int x, int y, PotionType type);
    
    virtual void usePotion(std::shared_ptr<PC> chr) = 0;
    
    // gets type of potion
    PotionType getType();
};

#endif
