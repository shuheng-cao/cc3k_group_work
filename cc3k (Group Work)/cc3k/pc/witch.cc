#include "witch.h"
using namespace std;

Witch::Witch(int x, int y, int hp, double atk, double def, string name):
PC{x, y, hp, atk, def, name} {
    setPFactor(0.5);
}
