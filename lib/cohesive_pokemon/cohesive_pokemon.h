#ifndef CAPTURED_POKEMON_H
#define CAPTURED_POKEMON_H

#include <cmath>
#include <map>
#include <vector>

#include "../game/game.h"
#include "../gamedata/gamedata.h"

typedef enum { GENDER_MALE, GENDER_FEMALE } Gender;

typedef enum {
  STATUM_HP,
  STATUM_ATTACK,
  STATUM_DEFENSE,
  STATUM_SPEED,
  STATUM_SPECIAL_ATTACK,
  STATUM_SPECIAL_DEFENSE
} Statum;

class CohesivePokemon : public Pokemon {
 private:
  int level;
  int generateIV(Statum statum);
  void setLevel(int level);

 public:
  int HP;
  int attack;
  int defense;
  int speed;
  int special_attack;
  int special_defense;
  Gender gender;
  bool shiny;
  CohesivePokemon(Pokemon pokemon) : Pokemon(pokemon) {
    this->shiny = rand() % 8912 == 0;
    this->gender = rand() % 2 ? GENDER_MALE : GENDER_FEMALE;

    int manhattanDistance =
        abs(game->map.x - MAP_WIDTH / 2) + abs(game->map.y - MAP_HEIGHT / 2);

    if (manhattanDistance <= 200) {
      this->setLevel(rand() % (manhattanDistance / 2) + 1);
    } else {
      this->setLevel(rand() % (100 - (manhattanDistance - 200) / 2) +
                     (manhattanDistance - 200) / 2);
    }
  }
  int getLevel() { return this->level; }
};

#endif