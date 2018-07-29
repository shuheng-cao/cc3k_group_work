#ifndef __TYPE_H__
#define __TYPE_H__

enum class PCType {SHADE, TROLL, GOBLIN, DROW, WITCH, VAMPIRE};
enum class EnemyType {HUMAN, MERCHANT, DRAGON, HALFLING, DWARF, ORC, ELF};
enum class HoardType {NORMALHOARD, SMALLHOARD, DRAGONHOARD, MERCHANTHOARD};
enum class PotionType {RH, BA, BD, PH, WA, WD};
enum class Direction { NW, N, NE, W, E, SW, S, SE };
enum class CellType {PC, ENEMY, POTION, GOLD, VWALL, HWALL, DOORWAY, PASSAGE, FLOOR, ABYSS, STAIR};
enum class CharacterState {MOVE, MISS, ATTACK, DEAD, INVALID};

#endif
