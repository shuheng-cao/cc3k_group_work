#ifndef __PH_H__
#define __PH_H__
#include "potion.h"


class PH final: public Potion {
    
public:
    PH(int x, int y);
    
    void usePotion(std::shared_ptr<PC> chr) override;
};


#endif
