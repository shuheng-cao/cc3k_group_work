#include "character.h"
#include "type.h"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;


struct Character::Info {
    Direction whereFrom ;
    int howManyDamage;
    string target ;
    int targetHp;
public:
    Info(Direction d = Direction::N, int dmg = 0, string t = "",
         int thp = 0): whereFrom{d}, howManyDamage{dmg},
    target{t}, targetHp{thp} {}
};


// state with common data in enemy and pc
class Character::State {
    int hp;
    double atk;
    double def;
    string name;
    
public:
    void initialize(int newHp, double newAtk, double newDef, string newName) {
        hp = newHp;
        atk = newAtk;
        def = newDef;
        name = newName;
    }
    
    int getHp() {
        return hp;
    }
    
    double getAtk() {
        return atk;
    }
    
    double getDef() {
        return def;
    }
    
    string getName() {
        return name;
    }
    
    void setHp(int newHp) {
        hp = newHp;
    }
    
    void setAtk(double newAtk){
        atk = newAtk;
    }
    
    void setDef(double newDef) {
        def = newDef;
    }
    
    void setName(string newName) {
        name = newName;
    }
};


class Character::BaseState {
    // base (max) data that can not exceed
    int baseHp;
    double baseAtk, baseDef;
    char symbol = '@';
    
public:
    BaseState(int newBaseHp, double newBaseAtk, double newBaseDef) {
        baseHp = newBaseHp;
        baseAtk = newBaseAtk;
        baseDef = newBaseDef;
    }
    
    int getBHp() {
        return baseHp;
    }
    
    double getBAtk() {
        return baseAtk;
    }
    
    double getBDef() {
        return baseDef;
    }
};


Character::Character(int x, int y, int hp, double atk, double def, string name):
Subject{x, y} {
    state = make_unique<State>();
    state->initialize(hp, atk, def, name);
    baseState = make_unique<BaseState>(hp, atk, def);
    myInfo = make_unique<Info>();
}


void Character::reset() {
    setAtk(baseState->getBAtk());
    setDef(baseState->getBDef());
}


//void Character::notify(Subject &whoFrom) {
void Character::resetObserver() {
}


// get the race of this character

string Character::getName() {
    return state->getName();
    
}


// set the name of this chracter
void Character::setName(string newName) {
    state->setName(newName);
    
}

// get methods

int Character::getHp() const{
    return state->getHp();
    
}

double Character::getAtk() const{
    return state->getAtk();
    
}

double Character::getDef() const{
    return state->getDef();
}

shared_ptr<Grid> Character::getMyGrid(){
    return myGrid;
}


// set methods


bool Character::comp(double a, double b){
    return (a < b);
}


void Character::setHp(int newHp) {
    if (getName() != "vampire") {
        state->setHp(max(0, newHp));
        state->setHp(min(baseState->getBHp(), getHp()));
    } else {
        state->setHp(max(0, newHp));
    }
    
}


void Character::setAtk(double newAtk) {
    state->setAtk(max(0.0, newAtk));
}


void Character::setDef(double newDef) {
    state->setDef( max(0.0,newDef));
    
}


void Character::setMyGrid(shared_ptr<Grid> g) {
    if (g == nullptr) {
        throw invalid_argument("no grid pointer");
    }
    myGrid = g;
    
    if (myGrid == nullptr) {
        throw invalid_argument("no mygrid");
    }
}


// attack
int Character::attack(shared_ptr<Character> chr) {
    // call attackedBy of the one being attacked
    int damageCaused = chr->attackedBy(shared_ptr<Character>
                                       (this, [](Character*){}));
    //cout << damageCaused << endl;
    // damageCause > 0 means real damage, didn't miss
    if (damageCaused) {
        setState(CharacterState::ATTACK);
        setTarget(chr->getName());
        setTargetHp(chr->getHp());
        setDamagesMade(damageCaused);
        
    } else {
        // no real damage, missed
        setState(CharacterState::MISS);
    }
    
    notifyObservers();
    return damageCaused;
}


int Character::attackedBy(shared_ptr<Character> chr) {
    int damage = ceil(100 / (100 + getDef()) * chr->getAtk());
    
    setHp(getHp() - damage);
    if (getHp() == 0) {
        setState(CharacterState::DEAD);
        notifyObservers();
    }
    return damage;
}


// get the position of next cell want to move to
pair<int, int> Character::nextCell(Direction dir) {
    int newX = getX();
    int newY = getY();
    switch (dir) {
        case (Direction::N):
            newX = newX - 1;
            break;
        case (Direction::S):
            newX = newX + 1;
            break;
        case (Direction::E):
            newY = newY + 1;
            break;
        case (Direction::W):
            newY = newY - 1;
            break;
        case (Direction::NE):
            newY = newY + 1;
            newX = newX - 1;
            break;
        case (Direction::SE):
            newY = newY + 1;
            newX = newX + 1;
            break;
        case (Direction::NW):
            newY = newY - 1;
            newX = newX - 1;
            break;
        case (Direction::SW):
            newY = newY - 1;
            newX = newX + 1;
            break;
    }
    return pair<int, int> (newX, newY);
    
}


// set currentState MOVE, MISS, DEAD, ATTACK, INVALID

void Character::setState(CharacterState myState) {
    currentState = myState;
}

CharacterState Character::getState() {
    return currentState;
}


void Character::setWhereFrom(Direction dir) {
    myInfo->whereFrom = dir;
}


// get what origianl its position is
Direction Character::getWhereFrom() {
    return myInfo->whereFrom;
}


// set how many damage made
void Character::setDamagesMade(int damage) {
    myInfo->howManyDamage = damage;
}

int Character::getDamagesMade() {
    return myInfo->howManyDamage;
}

void Character::setTarget(string which) {
    myInfo->target = which;
}

string Character::getTarget(){
    return myInfo->target;
}

void Character::setTargetHp(int thp){
    
    myInfo->targetHp = thp;
}

int Character::getTargetHp() {
    return myInfo->targetHp;
}

Character::~Character() = default;


