#ifndef __ORC_H__
#define __ORC_H__

#include "enemy.h"

class Orc: public Enemy {
public:
    Orc(int x, int y, std::string name = "orcs");
    int attack(std::shared_ptr<Character> chr);
    ~Orc() = default;
};

#endif 
