#ifndef __TREASURE_H__
#define __TREASURE_H__
#include "../item.h"
#include "../type.h"
#include "../pc/pc.h"

class PC;

class Treasure: public Item {
    int value;
    const char symbol = 'G';
    
public:
    Treasure(int x, int y, int val);
    
    // if it is picked by chr
    virtual void pickedBy(std::shared_ptr<PC> chr);
    
    // randomly generates normal or small pile of gold
    //and immediately adds to players' total.
    // (Only call upon the qualified enemies' demise.)
    virtual void addDemiseGold(std::shared_ptr<PC> chr);
    
    // gets type of treasure
    virtual HoardType getType();
};

#endif
