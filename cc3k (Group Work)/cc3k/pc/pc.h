#ifndef __PC_H__
#define __PC_H__

#include <algorithm>
#include "../subject.h"
#include "../observer.h"
#include "../character.h"
#include "../type.h"
#include "../grid.h"

class Potion;
class PC: public Character {
    
    int myScore = 0;
    double goldFactor = 1.0;
    double potionFactor = 1.0;
    int slainSteal = 0;
public:
    PC(int x, int y, int hp, double atk, double def, std::string name);
    
    virtual void consumePotion(std::shared_ptr<Potion> p);
    virtual void move(Direction dir) override;
    char getSymbol();
    int getScore();
    int getSteal();
    int getGFactor();
    int getPFactor();
    
    virtual void setGFactor(double gf);
    virtual void setPFactor(double pf);
    virtual void setSteal(int ss);
    void addScore(int n);
    
    virtual ~PC() = 0;
};

#endif
