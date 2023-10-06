#ifndef ROOM_H
#define ROOM_H

#include "../tile/tile.h"

#define ROOM_WIDTH 80
#define ROOM_HEIGHT 21

struct Map;
struct Trainer;

struct Room {
  int x, y;
  struct Tile tiles[ROOM_HEIGHT][ROOM_WIDTH];
  struct Tile *entrances[4];
  struct Trainer *trainers[ROOM_HEIGHT][ROOM_WIDTH];
};

int createRoom(struct Map *map, struct Room *room, int x, int y);
int destroyRoom(struct Room *room);
int chooseRandomTile(struct Room *room, struct Tile **tile);
int populateRoom(struct Room *room);
int createPath(struct Map *map, struct Room *room);

#endif