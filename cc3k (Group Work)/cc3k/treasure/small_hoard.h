#ifndef __SMALL_HOARD_H__
#define __SMALL_HOARD_H__
#include "treasure.h"

class SmallHoard final: public Treasure {
    const int value = 1;
    
public:
    SmallHoard(int x, int y);
};

#endif
