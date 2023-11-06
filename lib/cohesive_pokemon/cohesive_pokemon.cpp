#include "cohesive_pokemon.h"

#include <cmath>

int CohesivePokemon::generateIV(Statum statum) {
  PokemonStat baseStat;

  for (int i = 0; i < gameData->pokemonStats.size(); i++) {
    baseStat = gameData->pokemonStats[i];
    if (baseStat.pokemon_id == this->id && baseStat.stat_id == statum) {
      break;
    }
  }

  int iv = rand() % 16;

  int constant = statum == HP ? this->level + 10 : 5;

  return floor(((((baseStat.base_stat) + iv) * 2) * this->level) / 100) +
         constant;
}

void CohesivePokemon::setLevel(int level) {
  this->level = level;

  this->HP = this->generateIV(STATUM_HP);
  this->attack = this->generateIV(STATUM_ATTACK);
  this->defense = this->generateIV(STATUM_DEFENSE);
  this->speed = this->generateIV(STATUM_SPEED);
  this->special_attack = this->generateIV(STATUM_SPECIAL_ATTACK);
  this->special_defense = this->generateIV(STATUM_SPECIAL_DEFENSE);
}