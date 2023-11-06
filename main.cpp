#include <ncurses.h>

#include <cstring>
#include <iostream>

#include "./lib/game/game.h"
#include "./lib/gamedata/gamedata.h"
#include "./lib/map/map.h"
#include "./lib/render/render.h"
#include "./util/debug/debug.h"

GameData* gameData = new GameData();
Game* game = new Game();

int main(int argc, char* argv[]) {
  int numTrainers = 10;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--numtrainers") == 0) {
      if (i + 1 == argc) {
        std::cout << "Proper usage: " << argv[0] << " --numtrainers <number>"
                  << std::endl;
        return 1;
      }

      numTrainers = atoi(argv[i + 1]);
    } else if (strcmp(argv[i], "--debug") == 0) {
      startDebugging();
    }
  }

  debug("Starting the game.");

  // Making ncurses do its magic
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  // Setting the seed for the random number generator.
  time_t seed = time(NULL);
  srand(seed);

  // Creating the game.
  game->seed = seed;

  createGame(game, numTrainers);

  // Initialize colors
  initializeColors();

  // Starting the game loop
  startLoop(game);

  // Destroying the game (freeing dynamically allocated memory).
  destroyGame(game);

  // Killing ncurses
  endwin();

  // Stop the debugger
  if (isDebugging()) {
    stopDebugging();
  }

  return 0;
}