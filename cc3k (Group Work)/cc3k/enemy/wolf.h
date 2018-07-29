#ifndef __WOLF_H__
#define __WOLF_H__

#include "enemy.h"

class Wolf: public Enemy {
public:
    Wolf(int x, int y, std::string name = "wolf");
    ~Wolf() = default;
};

#endif
