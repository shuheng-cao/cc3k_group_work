#ifndef __MERCHANT_HOARD_H__
#define __MERCHANT_HOARD_H__
#include "treasure.h"


class MerchantHoard final: public Treasure {
    const int value = 4;
    
public:
    MerchantHoard(int x, int y);
};


#endif
