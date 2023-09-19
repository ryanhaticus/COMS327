#include "../tile/tile.h"

#ifndef ENEMY_H
#define ENEMY_H

enum TrainerType { HIKER, RIVAL };

struct Trainer {
  enum TrainerType type;
  int x, y;
};

int getHikerTileCost(struct Tile *tile);
int getRivalTileCost(struct Tile *tile);

#endif