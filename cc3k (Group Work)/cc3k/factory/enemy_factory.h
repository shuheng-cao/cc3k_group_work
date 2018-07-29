#ifndef ENMYFAC_H
#define ENMYFAC_H

#include "factory.h"
#include "../type.h"
#include "../enemy/enemy.h"
#include "../enemy/human.h"
#include "../enemy/merchant.h"
#include "../enemy/halfing.h"
#include "../enemy/dwarf.h"
#include "../enemy/orc.h"
#include "../enemy/elf.h"


class EnemyFactory: public Factory{
    EnemyType enemyList[18] = {EnemyType::HUMAN, EnemyType::HUMAN,
        EnemyType::HUMAN, EnemyType::HUMAN, EnemyType::MERCHANT,
        EnemyType::MERCHANT, EnemyType::DWARF, EnemyType::DWARF,
        EnemyType::DWARF, EnemyType::HALFLING, EnemyType::HALFLING,
        EnemyType::HALFLING, EnemyType::HALFLING, EnemyType::HALFLING,
        EnemyType::ELF, EnemyType::ELF, EnemyType::ORC, EnemyType::ORC};
    
    EnemyType chooseType();
public:
    std::shared_ptr<Enemy> create(int x, int y);
    
};
#endif

