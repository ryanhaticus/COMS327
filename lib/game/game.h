#ifndef GAME_H
#define GAME_H

#include "../map/map.h"
#include "../player/player.h"

typedef struct Game {
  Map map;
  Player player;
  int seed;
  char status[128];
} Game;

int createGame(Game *game, int trainersPerRoom);
int destroyGame(Game *game);
void startLoop(Game *game);

#endif