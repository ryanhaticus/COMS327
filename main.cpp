#include <ncurses.h>

#include <iostream>
#include <cstring>

#include "./lib/game/game.h"
#include "./lib/map/map.h"
#include "./lib/render/render.h"

int main(int argc, char *argv[]) {
  int numTrainers = 10;

  if (argc > 1 && strcmp(argv[1], "--numtrainers") == 0) {
    if (argc == 2) {
      std::cout << "Proper usage: " << argv[0] << " --numtrainers <number>"
                << std::endl;
      return 1;
    }

    numTrainers = atoi(argv[2]);
  }

  // Making ncurses do its magic
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  // Setting the seed for the random number generator.
  time_t seed = time(NULL);
  srand(seed);

  // Creating the game.
  struct Game game;
  game.seed = seed;

  createGame(&game, numTrainers);

  // Initialize colors
  initializeColors();

  // Starting the game loop
  startLoop(&game);

  // Destroying the game (freeing dynamically allocated memory).
  destroyGame(&game);

  // Killing ncurses
  endwin();

  return 0;
}