#ifndef MAP_H
#define MAP_H

#include "../room/room.h"

#define MAP_WIDTH 401
#define MAP_HEIGHT 401

#define N 0
#define E 1
#define S 2
#define W 3

struct Map {
  int x, y;
  struct Room *rooms[MAP_HEIGHT][MAP_WIDTH];
  int trainersPerRoom;
};

int createMap(struct Map *map, int trainersPerRoom);
int destroyMap(struct Map *map);

#endif