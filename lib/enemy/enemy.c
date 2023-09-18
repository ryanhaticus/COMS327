#include "enemy.h"

int getHikerTileCost(struct Tile *tile) {
  switch (tile->type) {
    case 0:
      break;  // EMPTY
    case 1:   // GRASS
    case 2:   // GRASS_2
      return 10;
    case 3:  // TALL_GRASS
    case 4:  // TALL_GRASS_2
      return 15;
    case 5:  // FOREST
      return __INT_MAX__;
    case 6:  // WATER
      return __INT_MAX__;
    case 7:  // BOULDER
      return __INT_MAX__;
    case 8:  // PATH
      return 10;
    case 9:  // POKEMON_CENTER
      return 50;
    case 10:  // POKEMART
      return 50;
  }

  return 0;
}

int getRivalTileCost(struct Tile *tile) {
  switch (tile->type) {
    case 0:
      break;  // EMPTY
    case 1:   // GRASS
    case 2:   // GRASS_2
      return 10;
    case 3:  // TALL_GRASS
    case 4:  // TALL_GRASS_2
      return 20;
    case 5:  // FOREST
      return __INT_MAX__;
    case 6:  // WATER
      return __INT_MAX__;
    case 7:  // BOULDER
      return __INT_MAX__;
    case 8:  // PATH
      return 10;
    case 9:  // POKEMON_CENTER
      return 50;
    case 10:  // POKEMART
      return 50;
  }

  return 0;
}