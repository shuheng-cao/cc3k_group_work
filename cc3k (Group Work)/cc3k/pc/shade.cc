#include "shade.h"
using namespace std;

Shade::Shade(int x, int y, int hp, double atk, double def, string name): PC{x, y, hp , atk, def, name} {
    setGFactor(1.5);
}
