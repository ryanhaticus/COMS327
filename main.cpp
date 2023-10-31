#include <ncurses.h>

#include <cstring>
#include <iostream>

#include "./lib/game/game.h"
#include "./lib/gamedata/gamedata.h"
#include "./lib/map/map.h"
#include "./lib/render/render.h"
#include "./util/debug/debug.h"

int main(int argc, char* argv[]) {
  int numTrainers = 10;

  /*
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
  }*/

  std::string properUsage = "Proper usage: " + std::string(argv[0]) +
                            " <flag>\n" +
                            "Valid flags: pokemon, moves, pokemon_moves, "
                            "pokemon_species,\nexperience, type_names, "
                            "pokemon_stats, stats, pokemon_types";

  if (argc < 2) {
    std::cout << properUsage << std::endl;
    return 1;
  }

  GameData* gameData = new GameData();

  if (strcmp(argv[1], "pokemon") == 0) {
    gameData->loadPokemon();
    gameData->printPokemon();
  } else if (strcmp(argv[1], "moves") == 0) {
    gameData->loadMoves();
    gameData->printMoves();
  } else if (strcmp(argv[1], "pokemon_moves") == 0) {
    gameData->loadPokemonMoves();
    gameData->printPokemonMoves();
  } else if (strcmp(argv[1], "pokemon_species") == 0) {
    gameData->loadPokemonSpecies();
    gameData->printPokemonSpecies();
  } else if (strcmp(argv[1], "experience") == 0) {
    gameData->loadExperience();
    gameData->printExperience();
  } else if (strcmp(argv[1], "type_names") == 0) {
    gameData->loadTypeNames();
    gameData->printTypeNames();
  } else if (strcmp(argv[1], "pokemon_stats") == 0) {
    gameData->loadPokemonStats();
    gameData->printPokemonStats();
  } else if (strcmp(argv[1], "stats") == 0) {
    gameData->loadStats();
    gameData->printStats();
  } else if (strcmp(argv[1], "pokemon_types") == 0) {
    gameData->loadPokemonTypes();
    gameData->printPokemonTypes();
  } else {
    std::cout << properUsage << std::endl;
    return 1;
  }

  delete gameData;

  return 0;

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
  Game game;
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

  // Stop the debugger
  if (isDebugging()) {
    stopDebugging();
  }

  return 0;
}