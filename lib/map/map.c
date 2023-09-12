#include "map.h"

#include <math.h>
#include <stdio.h>

#include "../../util/io/io.h"

int createMap(struct Map *map) {
  // map->x = (int)floor(MAP_WIDTH / 2);
  // map->y = (int)floor(MAP_HEIGHT / 2);
  map->x = 0;
  map->y = 0;

  int y, x;

  int createdRooms = 0;

  for (y = 0; y < MAP_HEIGHT; y++) {
    for (x = 0; x < MAP_WIDTH; x++) {
      double percentComplete = createdRooms * 100 / (MAP_WIDTH * MAP_HEIGHT);

      printf(CLEAR_SCREEN);
      printf("Map is loading... %d%% complete.\n", (int)percentComplete);

      createRoom(map, &map->rooms[y][x], x, y);
      createdRooms++;
    }
  }

  return 0;
}

void renderMap(struct Map *map) {
  struct Room currentRoom = map->rooms[map->y][map->x];

  printf(CLEAR_SCREEN);

  renderRoom(&currentRoom);
}