#include "wolf.h"

// The wolf is basically a test enemy who have no ATK
//  but high extremely high HP

Wolf::Wolf(int x, int y, std::string name): Enemy(x, y, 500, 0, 0, name) {}
