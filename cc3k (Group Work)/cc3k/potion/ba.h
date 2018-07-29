#ifndef __BA_H__
#define __BA_H__
#include "potion.h"


class BA final: public Potion {
    PotionType type = PotionType::BA;
    
public:
    BA(int x, int y);
    
    // uses potion - Boost Atk
    void usePotion(std::shared_ptr<PC> chr) override;
};


#endif
