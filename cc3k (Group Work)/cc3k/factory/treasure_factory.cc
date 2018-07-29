#include "treasure_factory.h"
using namespace std;

HoardType TreasureFactory::chooseType() {
    int randNum = rand() % 8;
    return HoardList[randNum];
}

shared_ptr<Treasure> TreasureFactory::create(int x, int y) {
    HoardType type = chooseType();
    shared_ptr<Treasure> hd = nullptr;
    if (type == HoardType::NORMALHOARD) {
        hd = make_shared<NormalHoard>(x, y);
    } else if (type == HoardType::SMALLHOARD) {
        hd = make_shared<SmallHoard>(x, y);
    }  else if (type == HoardType::DRAGONHOARD) {
        hd = make_shared<DragonHoard>(x, y);
    }
    return hd;
}
