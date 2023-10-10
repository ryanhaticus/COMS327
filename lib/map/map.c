#include "map.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int createMap(Map *map, int trainersPerRoom) {
  int y, x;

  for (y = 0; y < MAP_HEIGHT; y++) {
    for (x = 0; x < MAP_WIDTH; x++) {
      map->rooms[y][x] = NULL;
    }
  }

  map->x = (int)floor(MAP_WIDTH / 2);
  map->y = (int)floor(MAP_HEIGHT / 2);

  map->trainersPerRoom = trainersPerRoom;

  Room *room = malloc(sizeof(Room));

  createRoom(map, room, map->x, map->y);

  map->rooms[map->y][map->x] = room;

  return 0;
}

int destroyMap(Map *map) {
  int y, x;

  for (y = 0; y < MAP_HEIGHT; y++) {
    for (x = 0; x < MAP_WIDTH; x++) {
      Room *room = map->rooms[y][x];

      if (room == NULL) {
        continue;
      }

      destroyRoom(room);
      map->rooms[y][x] = NULL;
    }
  }

  return 0;
}