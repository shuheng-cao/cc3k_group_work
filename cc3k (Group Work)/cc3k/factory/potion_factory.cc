#include "potion_factory.h"

using namespace std;

PotionType PotionFactory::chooseType() {
    int randNum = rand() % 6;
    return potionList[randNum];
}


shared_ptr<Potion> PotionFactory::create(int x, int y) {
    PotionType type = chooseType();
    shared_ptr<Potion> pt = nullptr;
    if (type == PotionType::RH) {
        pt = make_shared<RH>(x, y);
    } else if (type == PotionType::BA) {
        pt = make_shared<BA>(x, y);
    }  else if (type == PotionType::BD) {
        pt = make_shared<BD>(x, y);
    }  else if (type == PotionType::PH) {
        pt = make_shared<PH>(x, y);
    }  else if (type == PotionType::WA) {
        pt =make_shared<WA>(x, y);
    }  else if (type == PotionType::WD) {
        pt = make_shared<WD>(x, y);
    }
    return pt;
}
