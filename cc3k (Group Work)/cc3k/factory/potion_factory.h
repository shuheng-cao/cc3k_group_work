#ifndef POTFACTORY_H
#define POTFACTORY_H

#include "factory.h"
#include "../type.h"
#include "../potion/potion.h"
#include "../potion/wa.h"
#include "../potion/wd.h"
#include "../potion/rh.h"
#include "../potion/ph.h"
#include "../potion/ba.h"
#include "../potion/bd.h"


class PotionFactory: public Factory {
    PotionType potionList[6] = {PotionType::RH, PotionType::BA,
        PotionType::BD, PotionType::PH, PotionType::WA, PotionType::WD};
    
    PotionType chooseType();
public:
    std::shared_ptr<Potion> create(int x, int y);
};


#endif
