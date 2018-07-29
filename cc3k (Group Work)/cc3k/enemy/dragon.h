#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "enemy.h"

class DragonHoard;

class Dragon: public Enemy {
    std::shared_ptr<DragonHoard> myHoard;
public:
//    void setDrangonHoard(std::shared_ptr<DragonHoard>);
    Dragon(std::shared_ptr<DragonHoard>, int x, int y,
           std::string name = "dragon");
    void move(Direction dir) override;
    void setMyHoard(std::shared_ptr<DragonHoard> hoard);
    std::shared_ptr<DragonHoard> getMyHoard();
    ~Dragon() = default;
};

#endif
