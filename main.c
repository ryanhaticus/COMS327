#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./lib/game/game.h"
#include "./lib/map/map.h"

int main(int argc, char* argv[]) {
  srand(time(NULL));

  struct Game game;

  createGame(&game);

  startLoop(&game);

  destroyGame(&game);

  return 0;
}