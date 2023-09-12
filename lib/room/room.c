#include "room.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../util/queue/queue.h"
#include "../map/map.h"

int createRoom(struct Map *map, struct Room *room, int i, int j) {
  room->x = i;
  room->y = j;

  int y, x;

  for (y = 0; y < ROOM_HEIGHT; y++) {
    for (x = 0; x < ROOM_WIDTH; x++) {
      createTile(&room->tiles[y][x], EMPTY, x, y);
    }
  }

  populateRoom(room);
  createPath(map, room);

  return 0;
}

void renderRoom(struct Room *room) {
  int y, x;

  for (y = 0; y < ROOM_HEIGHT; y++) {
    for (x = 0; x < ROOM_WIDTH; x++) {
      struct Tile tile = room->tiles[y][x];

      printf("%c", getTileCharacter(&tile));
    }

    printf("\n");
  }
}

int chooseRandomTile(struct Room *room, struct Tile **tile) {
  int y, x;

  y = rand() % ROOM_HEIGHT;
  x = rand() % ROOM_WIDTH;

  *tile = &room->tiles[y][x];

  return 0;
}

int populateRoom(struct Room *room) {
  struct Tile *tile[NUM_REGION_TILES];

  struct Queue regionQueue;
  createQueue(&regionQueue);

  int i;

  for (i = 0; i < NUM_REGION_TILES; i++) {
    int hasDistance = 0;

    while (!hasDistance) {
      chooseRandomTile(room, &tile[i]);

      if (tile[i]->type != EMPTY) {
        continue;
      }

      hasDistance = 1;

      int j;

      for (j = 0; j < i; j++) {
        if (getTileDistance(tile[i], tile[j]) < 12) {
          hasDistance = 0;
          break;
        }
      }

      if (!hasDistance) {
        continue;
      }

      tile[i]->type = i + NUM_SPECIAL_TILES;

      enqueue(&regionQueue, tile[i]);
    }
  }

  while (regionQueue.size > 0) {
    struct Tile *currentTile;
    dequeue(&regionQueue, (void **)&currentTile);

    int y, x;

    for (y = currentTile->y - 1; y <= currentTile->y + 1; y++) {
      for (x = currentTile->x - 1; x <= currentTile->x + 1; x++) {
        if ((y == currentTile->y && x == currentTile->x) || y < 0 ||
            y >= ROOM_HEIGHT || x < 0 || x >= ROOM_WIDTH) {
          continue;
        }

        struct Tile *adjacentTile = &room->tiles[y][x];

        if (adjacentTile->type != EMPTY) {
          continue;
        }

        adjacentTile->type = currentTile->type;

        enqueue(&regionQueue, adjacentTile);
      }
    }
  }

  for (i = 0; i < ROOM_WIDTH; i++) {
    room->tiles[0][i].type = BOULDER;
    room->tiles[ROOM_HEIGHT - 1][i].type = BOULDER;
  }

  for (i = 0; i < ROOM_HEIGHT; i++) {
    room->tiles[i][0].type = BOULDER;
    room->tiles[i][ROOM_WIDTH - 1].type = BOULDER;
  }

  int numBoulders = rand() % 5 + 8;

  for (i = 0; i < numBoulders; i++) {
    struct Tile *currentTile;

    chooseRandomTile(room, &currentTile);

    if (currentTile->type == WATER) {
      continue;
    }

    currentTile->type = BOULDER;
  }

  return 0;
}

int createPath(struct Map *map, struct Room *room) {
  int pathAllowed[4] = {room->y > 0, room->x == ROOM_WIDTH,
                        room->y == ROOM_HEIGHT, room->x > 0};  // N, E, S, W

  int y, x;

  if (pathAllowed[W]) {
    struct Tile *adjacentEntrance =
        map->rooms[room->y][room->x - 1].entrances[E];
    room->entrances[W] = &room->tiles[adjacentEntrance->y][0];
  } else {
    y = rand() % (ROOM_HEIGHT - 3) + 2;
    room->entrances[W] = &room->tiles[y][0];
  }

  if (pathAllowed[N]) {
    struct Tile *adjacentEntrance =
        map->rooms[room->y - 1][room->x].entrances[S];
    room->entrances[N] = &room->tiles[0][adjacentEntrance->x];
  } else {
    x = rand() % (ROOM_WIDTH - 3) + 2;
    room->entrances[N] = &room->tiles[0][x];
  }

  while (room->entrances[E] == NULL ||
         room->entrances[E]->x == room->entrances[W]->x) {
    y = rand() % (ROOM_HEIGHT - 2) + 1;
    room->entrances[E] = &room->tiles[y][ROOM_WIDTH - 1];
  }

  while (room->entrances[S] == NULL ||
         room->entrances[S]->y == room->entrances[N]->y) {
    x = rand() % (ROOM_WIDTH - 2) + 1;
    room->entrances[S] = &room->tiles[ROOM_HEIGHT - 1][x];
  }

  int horzPathStartY = room->entrances[W]->y;
  int horzPathEndY = room->entrances[E]->y;

  int horzPivotX = rand() % (ROOM_WIDTH / 2) + 16;

  int i;

  for (i = (pathAllowed[W] ? 0 : 1); i <= horzPivotX; i++) {
    room->tiles[horzPathStartY][i].type = PATH;
  }

  int vertDirection = horzPathStartY < horzPathEndY ? 1 : -1;

  int horzPivotY = horzPathStartY;

  while (horzPivotY != horzPathEndY) {
    horzPivotY += vertDirection;

    room->tiles[horzPivotY][horzPivotX].type = PATH;
  }

  for (i = horzPivotX; i < (pathAllowed[E] ? ROOM_WIDTH : ROOM_WIDTH - 1);
       i++) {
    room->tiles[horzPathEndY][i].type = PATH;
  }

  int vertPathStartX = room->entrances[N]->x;
  int vertPathEndX = room->entrances[S]->x;

  int vertPivotY = rand() % (ROOM_HEIGHT / 2) + 6;

  for (i = (pathAllowed[N] ? 0 : 1); i <= vertPivotY; i++) {
    room->tiles[i][vertPathStartX].type = PATH;
  }

  int horzDirection = vertPathStartX < vertPathEndX ? 1 : -1;

  int vertPivotX = vertPathStartX;

  while (vertPivotX != vertPathEndX) {
    vertPivotX += horzDirection;

    room->tiles[vertPivotY][vertPivotX].type = PATH;
  }

  for (i = vertPivotY; i < (pathAllowed[S] ? ROOM_HEIGHT : ROOM_HEIGHT - 1);
       i++) {
    room->tiles[i][vertPathEndX].type = PATH;
  }

  return 0;
}