#ifndef __RH_H__
#define __RH_H__
#include "potion.h"


class RH final: public Potion {
    
public:
    RH(int x, int y);
    
    // uses potion - Restore Health
    void usePotion(std::shared_ptr<PC> chr) override;
};


#endif
