#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

typedef class CohesivePokemon CohesivePokemon;
typedef class Game Game;

class Player {
 private:
  void generateStarters();

 public:
  int x, y;
  int flying;
  std::string input;
  std::vector<CohesivePokemon *> pokemon;
  int possibleStarters[3];

  Player() {
    x = 0;
    y = 0;
    flying = 0;
    input = "";
    this->generateStarters();
  }
};

int movePlayer(int move, Game *game);

#endif