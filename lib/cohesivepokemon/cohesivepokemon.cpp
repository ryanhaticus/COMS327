#include "cohesivepokemon.h"

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
  this->specialAttack = this->generateIV(STATUM_SPECIAL_ATTACK);
  this->specialDefense = this->generateIV(STATUM_SPECIAL_DEFENSE);
}

void CohesivePokemon::decideMoves() {
  std::vector<PokemonMove> possibleMoves;

  while (possibleMoves.size() == 0) {
    for (int i = 0; i < gameData->pokemonMoves.size(); i++) {
      PokemonMove possibleMove = gameData->pokemonMoves[i];

      if (possibleMove.level >= this->level &&
          possibleMove.pokemon_id == this->id) {
        possibleMoves.push_back(gameData->pokemonMoves[i]);
      }
    }

    if (possibleMoves.size() == 0) {
      this->setLevel(this->level + 1);
    }
  }

  int numMoves = possibleMoves.size() < 2 ? possibleMoves.size() : 2;

  for (int i = 0; i < numMoves; i++) {
    int randomIndex = rand() % possibleMoves.size();
    this->moves.push_back(possibleMoves[randomIndex]);
    possibleMoves.erase(possibleMoves.begin() + randomIndex);
  }
}