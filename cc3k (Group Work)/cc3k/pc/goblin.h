#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include "pc.h"

class Goblin: public PC {
public:
    Goblin(int x, int y, int hp, double atk, double def, std::string name);
    
};

#endif
