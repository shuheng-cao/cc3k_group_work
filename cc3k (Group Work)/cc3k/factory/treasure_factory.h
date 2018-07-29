#ifndef GOLDFAC_H
#define GOLDFAC_H

#include "../type.h"
#include "factory.h"
#include "../treasure/treasure.h"
#include "../treasure/small_hoard.h"
#include "../treasure/normal_hoard.h"
#include "../treasure/dragon_hoard.h"
#include "../treasure/merchant_hoard.h"

class TreasureFactory: public Factory {
    HoardType HoardList[8] = {HoardType::NORMALHOARD,HoardType::NORMALHOARD,
        HoardType::NORMALHOARD, HoardType::NORMALHOARD, HoardType::NORMALHOARD,
        HoardType::SMALLHOARD, HoardType::SMALLHOARD, HoardType::DRAGONHOARD};
    
    HoardType chooseType();
public:
    std::shared_ptr<Treasure> create(int x, int y);
};

#endif
