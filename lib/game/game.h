#ifndef GAME_H
#define GAME_H

#include "../map/map.h"
#include "../player/player.h"

#define MAX_INPUT_SIZE 256

struct Game
{
  struct Map map;
  struct Player player;
  int seed;
};

int createGame(struct Game *game);
int destroyGame(struct Game *game);
void renderGame(struct Game *game);
void startLoop(struct Game *game);

#endif