#ifndef __DROW_H__
#define __DROW_H__

#include "pc.h"

class Drow: public PC {
public:
    Drow(int x, int y, int hp, double atk, double def, std::string name);
};

#endif
