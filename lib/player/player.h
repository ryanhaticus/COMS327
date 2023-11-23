#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

typedef class CohesivePokemon CohesivePokemon;
typedef class Game Game;

class Player {
 private:
  void generateStarters();
  void chanceEncounter();

 public:
  int x, y;
  int flying;
  std::string input;
  std::vector<CohesivePokemon *> pokemon;
  int possibleStarters[3];
  int revives;
  int potions;
  int pokeballs;

  Player() {
    this->x = 0;
    this->y = 0;
    this->flying = 0;
    this->input = "";
    this->revives = 3;
    this->potions = 3;
    this->pokeballs = 10;
    this->generateStarters();
  }

  int movePlayer(int move, Game *game);
};

#endif