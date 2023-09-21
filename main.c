#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./lib/game/game.h"
#include "./lib/map/map.h"

int main(int argc, char* argv[]) {
  // Setting the seed for the random number generator.
  time_t seed = time(NULL);
  srand(seed);

  // Setting the title of the terminal window.
  printf("\033]0;Ryan Huellen\'s Pokemon Game\007");

  // Creating the game.
  struct Game game;
  game.seed = seed;

  createGame(&game);

  // Starting the game loop
  startLoop(&game);

  // Destroying the game (freeing dynamically allocated memory).
  destroyGame(&game);

  // Resetting the title of the terminal window.
  printf("\033]0;\007");

  return 0;
}