#include "game.h"

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../render/render.h"
#include "../room/room.h"
#include "../trainer/trainer.h"

void placePlayerRandomly(Map *map, Player *player) {
  Room *currentRoom = map->rooms[map->y][map->x];

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

int createGame(Game *game, int trainersPerRoom) {
  createMap(&game->map, trainersPerRoom);

  createPlayer(&game->player, 0, 0);

  strcpy(game->status, "Welcome to Ryan Huellen's Pokemon Game!");

  return 0;
}

int destroyGame(Game *game) {
  destroyMap(&game->map);

  return 0;
}

void startLoop(Game *game) {
  placePlayerRandomly(&game->map, &game->player);

  renderGame(game);

  while (1) {
    usleep(10000);

    moveTrainers(game->map.rooms[game->map.y][game->map.x], &game->player);

    renderGame(game);
  }
}