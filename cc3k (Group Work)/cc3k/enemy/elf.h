#ifndef __ELF_H__
#define __ELF_H__

#include "enemy.h"

class Elf: public Enemy {
public:
    Elf(int x, int y, std::string name = "elf");
    int attack(std::shared_ptr<Character> chr);
    ~Elf() = default;
};

#endif

