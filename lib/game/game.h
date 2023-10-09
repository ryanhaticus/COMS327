#ifndef GAME_H
#define GAME_H

#include "../map/map.h"
#include "../player/player.h"

#define MAX_INPUT_SIZE 256

struct Game {
  struct Map map;
  struct Player player;
  int seed;
  char status[128];
};

int createGame(struct Game *game, int trainersPerRoom);
int destroyGame(struct Game *game);
void startLoop(struct Game *game);

#endif