#include "../map/map.h"

#ifndef GAME_H
#define GAME_H

#define MAX_INPUT_SIZE 256

struct Game {
  struct Map map;
};

int createGame(struct Game *game);
int destroyGame(struct Game *game);
void renderGame(struct Game *game);
void startLoop(struct Game *game);

#endif