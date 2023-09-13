#include "tile.h"

#include <math.h>

int createTile(struct Tile *tile, int type, int x, int y) {
  tile->type = type;
  tile->x = x;
  tile->y = y;

  return 0;
}

int destroyTile(struct Tile *tile) {
  tile->type = EMPTY;
  tile->x = -1;
  tile->y = -1;

  return 0;
}

char getTileCharacter(struct Tile *tile) {
  switch (tile->type) {
    case 0:
      break;  // EMPTY
    case 1:   // GRASS
    case 2:   // GRASS_2
      return '.';
    case 3:  // TALL_GRASS
    case 4:  // TALL_GRASS_2
      return ':';
    case 5:  // FOREST
      return '^';
    case 6:  // WATER
      return '~';
    case 7:  // BOULDER
      return '%';
    case 8:  // PATH
      return '#';
    case 9:  // POKEMON_CENTER
      return 'C';
    case 10:  // POKEMART
      return 'M';
  }

  return '?';  // EMPTY
}

double getTileDistance(struct Tile *tile1, struct Tile *tile2) {
  return sqrt(pow(tile1->x - tile2->x, 2) + pow(tile1->y - tile2->y, 2));
}