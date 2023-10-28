#ifndef PLAYER_H
#define PLAYER_H

#include <string>

typedef class Game Game;

class Player {
 public:
  int x, y;
  int flying;
  std::string input;
  Player() {
    x = 0;
    y = 0;
    flying = 0;
    input = "";
  }
};

int movePlayer(int move, Game *game);

#endif