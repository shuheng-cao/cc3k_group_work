#ifndef __DWARF_H__
#define __DWARF_H__

#include "enemy.h"

class Dwarf: public Enemy {
public:
    Dwarf(int x, int y, std::string name = "dwarf");
    int attackedBy(std::shared_ptr<Character> chr) override;
    ~Dwarf() = default;
};

#endif 
