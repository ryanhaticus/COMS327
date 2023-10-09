#ifndef RENDER_H
#define RENDER_H

#include "../game/game.h"

enum Colors {
  COLOR_PLAYER = 1,
  COLOR_TRAINER,
  COLOR_GRASS,
  COLOR_TALL_GRASS,
  COLOR_FOREST,
  COLOR_WATER,
  COLOR_BOULDER,
  COLOR_PATH,
  COLOR_ENTRANCE,
  COLOR_POKEMON_CENTER,
  COLOR_POKEMART
};

void initializeColors();
void renderGame(struct Game *game);

#endif