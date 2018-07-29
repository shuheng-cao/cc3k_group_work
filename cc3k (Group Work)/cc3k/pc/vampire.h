#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "pc.h"

class Vampire: public PC {
public:
    Vampire(int x, int y, int hp, double atk, double def, std::string name);
    int attack(std::shared_ptr<Character> chr) override;
};

#endif
