#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./lib/game/game.h"
#include "./lib/map/map.h"

int main(int argc, char *argv[]) {
  // Making ncurses do its magic
  initscr();
  noecho();
  curs_set(0);

  // Setting the seed for the random number generator.
  time_t seed = time(NULL);
  srand(seed);

  // Creating the game.
  struct Game game;
  game.seed = seed;

  createGame(&game);

  // Starting the game loop
  startLoop(&game);

  // Destroying the game (freeing dynamically allocated memory).
  destroyGame(&game);

  // Killing ncurses
  endwin();

  return 0;
}