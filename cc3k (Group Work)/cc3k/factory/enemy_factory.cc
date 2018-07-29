#include "enemy_factory.h"
#include <time.h>
using namespace std;

EnemyType EnemyFactory::chooseType() {
    int randNum = rand() % 18;
    return enemyList[randNum];
}

shared_ptr<Enemy> EnemyFactory::create(int x, int y) {
    EnemyType type = chooseType();
    shared_ptr<Enemy> en = nullptr;
    if (type == EnemyType::HUMAN){
        en = make_shared<Human>(x, y, "human");
    } else if (type == EnemyType::MERCHANT) {
        en = make_shared<Merchant>(x, y, "merchant");
    } else if (type == EnemyType::HALFLING) {
        en = make_shared<Halfing>(x, y, "halfling");
    } else if (type == EnemyType::DWARF) {
        en = make_shared<Dwarf>(x, y, "dwarf");
    } else if (type == EnemyType::ORC) {
        en = make_shared<Orc>(x, y, "orc");
    } else if (type == EnemyType::ELF) {
        en = make_shared<Elf>(x, y, "elf");
    }
    return en;
}
