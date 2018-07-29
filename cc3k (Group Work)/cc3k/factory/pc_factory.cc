#include "pc_factory.h"

using namespace std;

shared_ptr<Subject> PCFactory::create(int x, int y, PCType type) {
    shared_ptr<Subject> pc = nullptr;
    if (type == PCType::SHADE) {
        pc = make_shared<Shade>(x, y, 125, 25, 25, "shade");
        
    } else if (type == PCType::TROLL) {
        pc = make_shared<Troll>(x, y, 120, 25, 15, "troll");
        
    } else if (type == PCType::GOBLIN) {
        pc = make_shared<Goblin>(x, y, 110, 15, 20,"goblin");
    } else if (type == PCType::DROW) {
        pc = make_shared<Drow>(x, y, 150, 25, 15,"drow");
    } else if (type == PCType::VAMPIRE) {
        pc = make_shared<Vampire>(x, y, 50, 25, 25,"vampire");
    } else if (type == PCType::WITCH) {
        pc = make_shared<Witch>(x, y, 125, 20, 30,"witch");
    }
    return pc;
}
