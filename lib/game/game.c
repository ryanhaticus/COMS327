#include "game.h"

#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../util/priorityqueue/priorityqueue.h"
#include "../player/player.h"
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

int createGame(struct Game *game) {
  createMap(&game->map);

  createPlayer(&game->player, 0, 0);

  return 0;
}

int destroyGame(struct Game *game) {
  destroyMap(&game->map);

  return 0;
}

void renderGame(struct Game *game) {
  int y, x;

  for (y = 0; y < ROOM_HEIGHT; y++) {
    for (x = 0; x < ROOM_WIDTH; x++) {
      if (x == game->player.x && y == game->player.y) {
        mvaddch(y, x, '@');
        continue;
      }

      struct Room room = *game->map.rooms[game->map.y][game->map.x];

      mvaddch(y, x, getTileCharacter(room.tiles[y][x]));

      if (room.trainers[y][x] != NULL) {
        mvaddch(y, x, getTrainerCharacter(room.trainers[y][x]));
        continue;
      }
    }
  }

  refresh();
}

void startLoop(struct Game *game) {
  placePlayerRandomly(&game->map, &game->player);

  renderGame(game);

  while (1) {
    usleep(3);

    moveTrainers(game->map.rooms[game->map.y][game->map.x], &game->player);

    renderGame(game);
  }
}