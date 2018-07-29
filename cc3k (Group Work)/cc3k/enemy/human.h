#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "enemy.h"

class Human: public Enemy {
public:
    Human(int x, int y, std::string name = "human");
    ~Human() = default;
};



#endif
