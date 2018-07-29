#include "dragon.h"
#include "../treasure/dragon_hoard.h"
#include "../grid.h"

using namespace std;

Dragon::Dragon(shared_ptr<DragonHoard> theHoard, int x, int y,
               string name):
Enemy{x, y, 150, 20, 20, name}, myHoard{theHoard} {}


void Dragon::move(Direction dir) {
    // Do nothing
}


void Dragon::setMyHoard(std::shared_ptr<DragonHoard> hoard) {
    myHoard = hoard;
}


std::shared_ptr<DragonHoard> Dragon::getMyHoard() {
     return myHoard;
}
