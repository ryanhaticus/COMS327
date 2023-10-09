#include "game.h"

#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../util/priorityqueue/priorityqueue.h"
#include "../player/player.h"
#include "../render/render.h"
#include "../trainer/trainer.h"

void placePlayerRandomly(struct Map *map, struct Player *player) {
  struct Room *currentRoom = map->rooms[map->y][map->x];

  int y = rand() % (ROOM_HEIGHT - 2) + 1;
  int x = rand() % (ROOM_WIDTH - 2) + 1;

  while (currentRoom->tiles[y][x].type != PATH ||
         currentRoom->trainers[y][x] != NULL) {
    y = rand() % (ROOM_HEIGHT - 2) + 1;
    x = rand() % (ROOM_WIDTH - 2) + 1;
  }

  player->x = x;
  player->y = y;
}

int createGame(struct Game *game, int trainersPerRoom) {
  createMap(&game->map, trainersPerRoom);

  createPlayer(&game->player, 0, 0);

  strcpy(game->status, "Welcome to Ryan Huellen's Pokemon Game!");

  return 0;
}

int destroyGame(struct Game *game) {
  destroyMap(&game->map);

  return 0;
}

void startLoop(struct Game *game) {
  placePlayerRandomly(&game->map, &game->player);

  renderGame(game);

  while (1) {
    usleep(10000);

    moveTrainers(game->map.rooms[game->map.y][game->map.x], &game->player);

    renderGame(game);
  }
}