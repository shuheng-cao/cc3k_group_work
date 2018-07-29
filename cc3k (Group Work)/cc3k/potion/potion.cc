#include "potion.h"


Potion::Potion(int x, int y, PotionType type): Item{x, y}, type{type} {}

// gets type of potion
PotionType Potion::getType() {
    return type;
}
