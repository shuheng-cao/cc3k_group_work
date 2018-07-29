#include "item.h"


Item::Item(int x, int y): Subject{x, y} {}

std::shared_ptr<PC> Item::getUser() {
    return user;
}

void Item::setUser(std::shared_ptr<PC> whouUsed) {
    user = whouUsed;
}
