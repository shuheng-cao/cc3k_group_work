#include "enemy.h"
#include "../observer.h"
#include "../type.h"
#include "../grid.h"
#include <ctime>
#include <math.h>
#include <iostream>

using namespace std;


// Private Helper, to get a random direction
Direction getRandomDir() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int myRandom = (rand() % 8);
    // return the corresponding direction
    return Direction(myRandom);
}


Enemy::Enemy(int x, int y, int hp, double atk, double def, std::string name):
    Character{x, y, hp, atk, def, name} {}


// I redefine the move for character. However, an enemy didn't need a Direction,
//  just ignore it
void Enemy::move(Direction dir) {
    // Move only when enemy is not frozen
    // - MARK: need to consider when to attack and when to move
    if (!frozen) {
        Direction myRandDir = getRandomDir();
        // The posn for nextCell
        pair<int, int> nextCell = Character::nextCell(myRandDir);
        // If nextCell is floor, then move. Otherwise do nothing
        if (myGrid->getCellType(nextCell) == CellType::FLOOR) {
            setState(CharacterState::MOVE);
            setWhereFrom(myRandDir);
            // Remember to check whether the enemy is dead in the notify
            this->notifyObservers();
            this->setX(nextCell.first);
            this->setY(nextCell.second);
        }
    }
}


int Enemy::attack(std::shared_ptr<Character> chr) {
    if (!frozen) {
        int missOrNot = rand() % 2;
        if (missOrNot) {
            // Successful attack
            int causedDamage = chr->attackedBy(shared_ptr<Character>
                                               (this, [](Character*){}));
            setState(CharacterState::ATTACK);
            setDamagesMade(causedDamage);
            setTarget(chr->getName());
            
            setTargetHp(chr->getHp());
            notifyObservers();
            return causedDamage;
        } else {
            // Unsuccessful attack
            setState(CharacterState::MISS);
            notifyObservers();
            return 0;
        }
    }
    // Should reach this only when we are frozen
    return -1;
}


// Inheriate the same attackby() from Character

int Enemy::attackedBy(std::shared_ptr<Character> chr) {
    int damage = ceil((100 / (100 + getDef())) * chr->getAtk());
    setHp(getHp() - damage);
    if (getHp() <= 0) {
        setState(CharacterState::DEAD);
        shared_ptr<PC> pc = dynamic_pointer_cast<PC>(chr);
        addDemiseGold(pc);
        notifyObservers();
    }
    return damage;
}


void Enemy::addDemiseGold(std::shared_ptr<PC> chr) {
    int pile = 0;
    pile = rand() % 2 + 1;   // 1 - small pile, 2 - normal pile
    
    // immediately adds to players' total score
    chr->addScore(floor((chr->getGFactor() * pile) + chr->getSteal()));
}


void Enemy::togglefreeze() {
    frozen = !frozen;
}


Enemy::~Enemy(){
    
}


