#ifndef __WD_H__
#define __WD_H__
#include "potion.h"


class WD final: public Potion {
    PotionType type = PotionType::WD;
    
public:
    WD(int x, int y);
    
    // uses potion - Wound Def
    void usePotion(std::shared_ptr<PC> chr) override;
};


#endif
