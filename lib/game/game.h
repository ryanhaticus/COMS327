#ifndef GAME_H
#define GAME_H

#include "../map/map.h"

struct Game {
  struct Map map;
};

int createGame(struct Game *game);

#endif