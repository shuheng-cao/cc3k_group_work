#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "subject.h"
#include "type.h"
#include <string>
#include <memory>

class Grid;

class Character: public Subject {
    class State;
    class BaseState;
    struct Info;
    std::unique_ptr<BaseState> baseState;
    std::unique_ptr<Info> myInfo;
    // add CharaterType
    CharacterState currentState;
    bool comp(double a, double b);
protected:
    std::unique_ptr<State> state;
    std::shared_ptr<Grid> myGrid;
    // add info
    
    
public:
    Character(int x, int y, int hp, double atk, double def, std::string name);
    virtual std::pair<int, int> nextCell(Direction dir) ;
    virtual void move(Direction dir) = 0;
    
    virtual int attack(std::shared_ptr<Character> chr);
    virtual int attackedBy(std::shared_ptr<Character> chr) ;
    
//    void notify(Subject &whoFrom) override;
    void resetObserver();
    void reset();
    virtual void setName(std::string newName);
    virtual void setHp(int newHp);
    virtual void setAtk(double newAtk);
    virtual void setDef(double newDef);
    virtual void setMyGrid(std::shared_ptr<Grid> g);
    //virtual void setDef(int newDef);
    virtual void setState(CharacterState myState);
    virtual CharacterState getState();
    virtual void setWhereFrom(Direction dir);
    virtual Direction getWhereFrom();
    virtual void setDamagesMade(int damage);
    virtual int getDamagesMade();
    virtual void setTarget(std::string which);
    virtual std::string getTarget();
    virtual void setTargetHp(int thp);
    virtual int getTargetHp();
    
    virtual std::string getName();
    virtual int getHp() const;
    virtual double getAtk() const;
    virtual double getDef() const;
    virtual std::shared_ptr<Grid> getMyGrid();
    ~Character();
};
#endif
