#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include "enemy.h"


class Merchant: public Enemy {
public:
    Merchant(int x, int y, std::string name = "merchant");
//    void killedBy(shared_ptr<Character> chr) override;
    int attackedBy(std::shared_ptr<Character> chr) override;
    ~Merchant()= default;
};

#endif
