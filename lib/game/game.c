#include "game.h"

int createGame(struct Game *game) {
  createMap(&game->map);

  return 0;
}