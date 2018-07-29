#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "../character.h"
#include "../type.h"
#include "../pc/pc.h"

class Grid;

class Enemy: public Character {
    bool frozen = false;
public:
    Enemy(int x, int y, int hp, double atk, double def, std::string name);
    virtual void move(Direction dir) override;
    virtual int attack(std::shared_ptr<Character> chr) override;
    virtual int attackedBy(std::shared_ptr<Character> chr) override;
    virtual void addDemiseGold(std::shared_ptr<PC> chr);
    virtual void togglefreeze();
    virtual ~Enemy() = 0;
};

#endif
