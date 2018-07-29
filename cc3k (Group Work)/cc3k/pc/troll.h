#ifndef __TROLL_H__
#define __TROLL_H__
#include "pc.h"

class Troll: public PC {
public:
    Troll(int x, int y, int hp, double atk, double def, std::string name);
    //void move(Direction dir) override;
//    void attack(Character* chr) override;
};

#endif 
