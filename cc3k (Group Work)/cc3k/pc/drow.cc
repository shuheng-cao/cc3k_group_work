#include "drow.h"
using namespace std;


Drow::Drow(int x, int y, int hp, double atk, double def, string name):
PC{x, y, hp, atk, def, name} {
    setPFactor(1.5);
}
