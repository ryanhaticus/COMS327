#include "trainer.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../util/queue/queue.h"
#include "../room/room.h"

int getTrainerTileCost(struct Trainer *trainer, struct Tile *tile) {
  switch (trainer->type) {
    case 0:
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
      break;
    case 1:
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
      break;
  }

  return 0;
}

struct TileWithCost {
  struct Tile *tile;
  int cost;
};

void getTrainerTravelCost(int costs[ROOM_HEIGHT][ROOM_WIDTH], struct Room *room,
                          struct Trainer *trainer, int endX, int endY) {
  for (int i = 0; i < ROOM_HEIGHT; i++) {
    for (int j = 0; j < ROOM_WIDTH; j++) {
      costs[i][j] = __INT_MAX__;
    }
  }

  struct Queue queue;
  createQueue(&queue);

  struct TileWithCost *tileWithCost = malloc(sizeof(struct TileWithCost));
  tileWithCost->tile = &room->tiles[endY][endX];
  tileWithCost->cost = 0;

  enqueue(&queue, tileWithCost);

  while (queue.size > 0) {
    struct TileWithCost *tileWithCost;
    dequeue(&queue, (void **)&tileWithCost);

    int x = tileWithCost->tile->x;
    int y = tileWithCost->tile->y;

    if (costs[y][x] != __INT_MAX__) {
      continue;
    }

    costs[y][x] = tileWithCost->cost;

    for (int i = y - 1; i <= y + 1; i++) {
      for (int j = x - 1; j <= x + 1; j++) {
        if (i < 0 || i >= ROOM_HEIGHT || j < 0 || j >= ROOM_WIDTH) {
          continue;
        }

        if (i == y && j == x) {
          continue;
        }

        if (room->tiles[i][j].type == BOULDER ||
            room->tiles[i][j].type == WATER ||
            room->tiles[i][j].type == FOREST) {
          continue;
        }

        if (costs[i][j] != __INT_MAX__) {
          continue;
        }

        struct TileWithCost *tileWithCost = malloc(sizeof(struct TileWithCost));
        tileWithCost->tile = &room->tiles[i][j];
        tileWithCost->cost =
            costs[y][x] + getTrainerTileCost(trainer, &room->tiles[i][j]);

        enqueue(&queue, tileWithCost);
      }
    }
  }

  destroyQueue(&queue);
}

void printTrainerTravelCost(struct Game *game, enum TrainerType type) {
  struct Trainer trainer;
  trainer.type = type;
  trainer.x = 0;
  trainer.y = 0;

  int arr[ROOM_HEIGHT][ROOM_WIDTH] = {0};

  getTrainerTravelCost(arr, game->map.rooms[game->map.y][game->map.x], &trainer,
                       game->player.x, game->player.y);

  for (int i = 0; i < ROOM_HEIGHT; i++) {
    for (int j = 0; j < ROOM_WIDTH; j++) {
      if (arr[i][j] == __INT_MAX__) {
        printf("   ");
        continue;
      }

      int val = arr[i][j] % 100;
      if (val == 0) {
        printf("00 ");
      } else if (val < 10) {
        printf("0%d ", val);
      } else {
        printf("%d ", val);
      }
    }
    printf("\n");
  }
}