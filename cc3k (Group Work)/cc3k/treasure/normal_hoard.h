#ifndef __NORMAL_HOARD_H__
#define __NORMAL_HOARD_H__
#include "treasure.h"

class NormalHoard final: public Treasure {
    const int value = 2;
    
public:
    NormalHoard(int x, int y);
};

#endif
