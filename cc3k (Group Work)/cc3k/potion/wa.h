#ifndef __WA_H__
#define __WA_H__
#include "potion.h"


class WA final: public Potion {
    PotionType type = PotionType::WA;
    
public:
    WA(int x, int y);
    
    // uses potion - Wound Atk
    void usePotion(std::shared_ptr<PC> chr) override;
    
};


#endif
