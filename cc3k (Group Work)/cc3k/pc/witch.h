#ifndef __WITCH_H__
#define __WITCH_H__

#include "pc.h"

class Witch : public PC {
public:
    Witch(int x, int y, int hp, double atk, double def, std::string name);
};

#endif 
