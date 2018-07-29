#ifndef __HALFING_H__
#define __HALFING_H__

#include "enemy.h"

class Halfing: public Enemy {
public:
    Halfing(int x, int y, std::string name = "halfling");
    int attackedBy(std::shared_ptr<Character> chr) override;
    ~Halfing() = default;
};



#endif /* halfing_hpp */
