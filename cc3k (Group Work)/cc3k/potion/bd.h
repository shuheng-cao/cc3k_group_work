#ifndef __BD_H__
#define __BD_H__
#include "potion.h"


class BD final: public Potion {
    PotionType type = PotionType::BD;
    
public:
    BD(int x, int y);
    
    // uses potion - Boost Def
    void usePotion(std::shared_ptr<PC> chr) override;
    
};

#endif
