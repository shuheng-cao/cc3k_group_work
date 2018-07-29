#ifndef PCFACTORY_H
#define PCFACTORY_H

#include "factory.h"
#include "../type.h"
#include "../pc/shade.h"
#include "../pc/troll.h"
#include "../pc/goblin.h"
#include "../pc/drow.h"
#include "../pc/vampire.h"
#include "../pc/witch.h"


class PCFactory: public Factory {
    
public:
    std::shared_ptr<Subject> create(int x, int y, PCType type);
};

#endif

