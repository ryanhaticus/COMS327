#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./lib/game/game.h"
#include "./lib/map/map.h"

int main(int argc, char* argv[]) {
  srand(time(NULL));

  struct Game* game = malloc(sizeof(struct Game));

  createGame(game);

  renderMap(&game->map);

  return 0;
}