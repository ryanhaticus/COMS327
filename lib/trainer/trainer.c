#include "trainer.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../util/priorityqueue/priorityqueue.h"

int getTrainerTileCost(Trainer *trainer, Room *room, Tile *tile) {
  if (room->trainers[tile->y][tile->x] != NULL) {
    return __INT_MAX__;
  }

  switch (trainer->type) {
    case HIKER:
      switch (tile->type) {
        case EMPTY:
          break;       // EMPTY
        case GRASS:    // GRASS
        case GRASS_2:  // GRASS_2
          return 10;
        case TALL_GRASS:    // TALL_GRASS
        case TALL_GRASS_2:  // TALL_GRASS_2
          return 15;
        case FOREST:  // FOREST
          return __INT_MAX__;
        case WATER:  // WATER
          return __INT_MAX__;
        case BOULDER:  // BOULDER
          return __INT_MAX__;
        case PATH:  // PATH
          return 10;
        case ENTRANCE:  // ENTRANCE
          return __INT_MAX__;
        case POKEMON_CENTER:  // POKEMON_CENTER
          return 50;
        case POKEMART:  // POKEMART
          return 50;
      }
      break;
    case RIVAL:
      switch (tile->type) {
        case EMPTY:
          break;       // EMPTY
        case GRASS:    // GRASS
        case GRASS_2:  // GRASS_2
          return 10;
        case TALL_GRASS:    // TALL_GRASS
        case TALL_GRASS_2:  // TALL_GRASS_2
          return 20;
        case FOREST:  // FOREST
          return __INT_MAX__;
        case WATER:  // WATER
          return __INT_MAX__;
        case BOULDER:  // BOULDER
          return __INT_MAX__;
        case PATH:  // PATH
          return 10;
        case ENTRANCE:  // ENTRANCE
          return __INT_MAX__;
        case POKEMON_CENTER:  // POKEMON_CENTER
          return 50;
        case POKEMART:  // POKEMART
          return 50;
      }
    case PACER:
    case EXPLORER:
      switch (tile->type) {
        case EMPTY:
          break;            // EMPTY
        case GRASS:         // GRASS
        case GRASS_2:       // GRASS_2
        case TALL_GRASS:    // TALL_GRASS
        case TALL_GRASS_2:  // TALL_GRASS_2
          return 0;
        case FOREST:   // FOREST
        case WATER:    // WATER
        case BOULDER:  // BOULDER
          return __INT_MAX__;
        case PATH:  // PATH
          return 0;
        case ENTRANCE:  // ENTRANCE
          return __INT_MAX__;
        case POKEMON_CENTER:  // POKEMON_CENTER
        case POKEMART:        // POKEMART
          return 0;
      }
      break;
    case WANDERER:  // Wanderer
      if (room->tiles[trainer->y][trainer->x].type != tile->type) {
        return __INT_MAX__;
      }

      return 0;
    case SENTRY:
      return 0;
  }

  return 0;
}

typedef struct {
  Tile *tile;
  int cost;
} TileWithCost;

void getTrainerTravelCost(int costs[ROOM_HEIGHT][ROOM_WIDTH], Room *room,
                          Trainer *trainer, Player *player) {
  for (int i = 0; i < ROOM_HEIGHT; i++) {
    for (int j = 0; j < ROOM_WIDTH; j++) {
      costs[i][j] = __INT_MAX__;
    }
  }

  PriorityQueue queue;
  createPriorityQueue(&queue);

  TileWithCost *tileWithCost = malloc(sizeof(TileWithCost));
  tileWithCost->tile = &room->tiles[player->y][player->x];
  tileWithCost->cost = 0;

  enqueueWithPriority(&queue, tileWithCost, 0);

  while (queue.size > 0) {
    TileWithCost *tileWithCost;
    dequeueWithPriority(&queue, (void **)&tileWithCost);

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

        if (costs[i][j] != __INT_MAX__) {
          continue;
        }

        int trainerTileCost =
            getTrainerTileCost(trainer, room, &room->tiles[i][j]);

        if (trainerTileCost == __INT_MAX__) {
          continue;
        }

        TileWithCost *tileWithCost = malloc(sizeof(TileWithCost));
        tileWithCost->tile = &room->tiles[i][j];

        tileWithCost->cost = costs[y][x] + trainerTileCost;

        enqueueWithPriority(&queue, tileWithCost, tileWithCost->cost);
      }
    }
  }

  costs[player->y][player->x] = __INT_MAX__;

  destroyPriorityQueue(&queue);
}

void placeTrainerInRoom(Trainer *trainersInRoom[ROOM_HEIGHT][ROOM_WIDTH],
                        Trainer *trainer, Room *room) {
  int x, y;

  do {
    x = rand() % (ROOM_WIDTH - 4) + 2;
    y = rand() % (ROOM_HEIGHT - 4) + 2;

    trainer->x = x;
    trainer->y = y;
  } while (getTrainerTileCost(trainer, room, &room->tiles[y][x]) ==
               __INT_MAX__ ||
           room->tiles[y][x].type == PATH || trainersInRoom[y][x] != NULL);

  trainersInRoom[y][x] = trainer;
}

char getTrainerCharacter(Trainer *trainer) {
  switch (trainer->type) {
    case HIKER:
      return 'h';
    case RIVAL:
      return 'r';
    case PACER:
      return 'p';
    case WANDERER:
      return 'w';
    case SENTRY:
      return 's';
    case EXPLORER:
      return 'e';
  }

  return '?';
}

int createTrainer(Trainer **trainer) {
  *trainer = malloc(sizeof(Trainer));

  if (trainer == NULL) {
    return 1;
  }

  (*trainer)->dir = rand() % 4;
  (*trainer)->type = rand() % NUM_TRAINERS;
  (*trainer)->x = 0;
  (*trainer)->y = 0;

  return 0;
}

void destroyTrainer(Trainer *trainer) { free(trainer); }

void moveTrainers(Room *room, Player *player) {
  static int initialized = 0;
  static PriorityQueue queue;
  static int curTime = 0;

  int y, x;

  if (!initialized) {
    initialized = 1;

    createPriorityQueue(&queue);

    for (y = 0; y < ROOM_HEIGHT; y++) {
      for (x = 0; x < ROOM_WIDTH; x++) {
        if (room->trainers[y][x] == NULL) {
          continue;
        }

        Trainer *trainer = room->trainers[y][x];

        if (trainer->type == SENTRY) {
          continue;
        }

        enqueueWithPriority(&queue, trainer, 0);
      }
    }
  }

  if (queue.size == 0) {
    return;
  }

  Trainer *trainer;
  dequeueWithPriority(&queue, (void **)&trainer);

  curTime++;

  switch (trainer->type) {
    case RIVAL:
    case HIKER: {
      int costs[ROOM_HEIGHT][ROOM_WIDTH];
      getTrainerTravelCost(costs, room, trainer, player);

      int minCost = __INT_MAX__;
      Tile *minTile = NULL;

      for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
          if (y == 0 && x == 0) {
            continue;
          }

          if (trainer->y + y < 0 || trainer->y + y >= ROOM_HEIGHT ||
              trainer->x + x < 0 || trainer->x + x >= ROOM_WIDTH) {
            continue;
          }

          if (costs[trainer->y + y][trainer->x + x] < minCost) {
            minCost = costs[trainer->y + y][trainer->x + x];
            minTile = &room->tiles[trainer->y + y][trainer->x + x];
          }
        }
      }

      if (minTile == NULL) {
        enqueueWithPriority(&queue, trainer, curTime);
        break;
      }

      room->trainers[trainer->y][trainer->x] = NULL;
      room->trainers[minTile->y][minTile->x] = trainer;

      trainer->x = minTile->x;
      trainer->y = minTile->y;

      enqueueWithPriority(&queue, trainer, curTime + minCost);

      curTime += minCost;

      break;
    }
    case PACER: {
      switch (trainer->dir) {
        case N:
          if (getTrainerTileCost(trainer, room,
                                 &room->tiles[trainer->y - 1][trainer->x]) !=
              __INT_MAX__) {
            room->trainers[trainer->y][trainer->x] = NULL;
            room->trainers[trainer->y - 1][trainer->x] = trainer;

            trainer->y--;
          } else {
            trainer->dir = E;
          }
          break;
        case E:
          if (getTrainerTileCost(trainer, room,
                                 &room->tiles[trainer->y][trainer->x + 1]) !=
              __INT_MAX__) {
            room->trainers[trainer->y][trainer->x] = NULL;
            room->trainers[trainer->y][trainer->x + 1] = trainer;

            trainer->x++;
          } else {
            trainer->dir = W;
          }

          break;
        case S:
          if (getTrainerTileCost(trainer, room,
                                 &room->tiles[trainer->y + 1][trainer->x]) !=
              __INT_MAX__) {
            room->trainers[trainer->y][trainer->x] = NULL;
            room->trainers[trainer->y + 1][trainer->x] = trainer;

            trainer->y++;
          } else {
            trainer->dir = N;
          }

          break;
        case W:
          if (getTrainerTileCost(trainer, room,
                                 &room->tiles[trainer->y][trainer->x - 1]) !=
              __INT_MAX__) {
            room->trainers[trainer->y][trainer->x] = NULL;
            room->trainers[trainer->y][trainer->x - 1] = trainer;

            trainer->x--;
          } else {
            trainer->dir = E;
          }

          break;
      }

      enqueueWithPriority(&queue, trainer, curTime);

      break;
    }
    case WANDERER:
    case EXPLORER: {
      switch (trainer->dir) {
        case N:
          if (getTrainerTileCost(trainer, room,
                                 &room->tiles[trainer->y - 1][trainer->x]) !=
                  __INT_MAX__ &&
              (trainer->type == EXPLORER ||
               room->tiles[trainer->y - 1][trainer->x].type ==
                   room->tiles[trainer->y][trainer->x].type)) {
            room->trainers[trainer->y][trainer->x] = NULL;
            room->trainers[trainer->y - 1][trainer->x] = trainer;

            trainer->y--;
          } else {
            trainer->dir = rand() % 4;
          }
          break;
        case E:
          if (getTrainerTileCost(trainer, room,
                                 &room->tiles[trainer->y][trainer->x + 1]) !=
                  __INT_MAX__ &&
              (trainer->type == EXPLORER ||
               room->tiles[trainer->y][trainer->x + 1].type ==
                   room->tiles[trainer->y][trainer->x].type)) {
            room->trainers[trainer->y][trainer->x] = NULL;
            room->trainers[trainer->y][trainer->x + 1] = trainer;

            trainer->x++;
          } else {
            trainer->dir = rand() % 4;
          }
          break;
        case S:
          if (getTrainerTileCost(trainer, room,
                                 &room->tiles[trainer->y + 1][trainer->x]) !=
                  __INT_MAX__ &&
              (trainer->type == EXPLORER ||
               room->tiles[trainer->y + 1][trainer->x].type ==
                   room->tiles[trainer->y][trainer->x].type)) {
            room->trainers[trainer->y][trainer->x] = NULL;
            room->trainers[trainer->y + 1][trainer->x] = trainer;

            trainer->y++;
          } else {
            trainer->dir = rand() % 4;
          }
          break;
        case W:
          if (getTrainerTileCost(trainer, room,
                                 &room->tiles[trainer->y][trainer->x - 1]) !=
                  __INT_MAX__ &&
              (trainer->type == EXPLORER ||
               room->tiles[trainer->y][trainer->x - 1].type ==
                   room->tiles[trainer->y][trainer->x].type)) {
            room->trainers[trainer->y][trainer->x] = NULL;
            room->trainers[trainer->y][trainer->x - 1] = trainer;

            trainer->x--;
          } else {
            trainer->dir = rand() % 4;
          }
          break;
      }

      enqueueWithPriority(&queue, trainer, curTime);

      break;
    }
    case SENTRY:
      break;
  }
}