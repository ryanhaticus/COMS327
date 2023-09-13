#include "../tile/tile.h"

#ifndef ROOM_H
#define ROOM_H

#define ROOM_WIDTH 80
#define ROOM_HEIGHT 21

struct Map;

struct Room {
  int x, y;
  struct Tile tiles[ROOM_HEIGHT][ROOM_WIDTH];
  struct Tile *entrances[4];
};

int createRoom(struct Map *map, struct Room *room, int x, int y);
int destroyRoom(struct Room *room);
void renderRoom(struct Room *room);
int chooseRandomTile(struct Room *room, struct Tile **tile);
int populateRoom(struct Room *room);
int createPath(struct Map *map, struct Room *room);

#endif