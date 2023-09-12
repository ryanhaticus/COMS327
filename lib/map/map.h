#include "../room/room.h"

#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 401
#define MAP_HEIGHT 401

#define N 0
#define E 1
#define S 2
#define W 3

struct Map {
  int x, y;
  struct Room rooms[MAP_HEIGHT][MAP_WIDTH];
};

int createMap(struct Map *map);
void renderMap(struct Map *map);

#endif