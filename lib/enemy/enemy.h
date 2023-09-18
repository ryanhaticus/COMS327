#include "../tile/tile.h"

#ifndef ENEMY_H
#define ENEMY_H

enum EnemyType { HIKER, RIVAL };

struct Enemy {
  enum EnemyType type;
  int x, y;
};

int getHikerTileCost(struct Tile *tile);
int getRivalTileCost(struct Tile *tile);

#endif