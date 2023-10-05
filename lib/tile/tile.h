#ifndef TILE_H
#define TILE_H

#define NUM_SPECIAL_TILES 1
enum SpecialTile { EMPTY = 0 };

#define NUM_REGION_TILES 6
enum RegionTile { GRASS = 1, GRASS_2, TALL_GRASS, TALL_GRASS_2, FOREST, WATER };

enum EnvironmentTile { BOULDER = 7, PATH, ENTRANCE };

enum BuildingTile {
  POKEMON_CENTER = 10,
  POKEMART,
};

struct Tile {
  int type;
  int x, y;
};

int createTile(struct Tile *tile, int type, int x, int y);
int destroyTile(struct Tile *tile);
char getTileCharacter(struct Tile tile);
double getTileDistance(struct Tile tile1, struct Tile tile2);
double getDistance(int x1, int y1, int x2, int y2);

#endif