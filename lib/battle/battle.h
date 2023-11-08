#ifndef BATTLE_H
#define BATTLE_H

typedef class Trainer Trainer;
typedef class Game Game;
typedef class CohesivePokemon CohesivePokemon;

typedef enum { BATTLE_TYPE_TRAINER, BATTLE_TYPE_POKEMON } BattleType;

class Battle {
 public:
  Trainer* againstTrainer;
  CohesivePokemon* againstPokemon;
  BattleType type;
  void startTrainerBattle(Trainer* against);
  void startPokemonBattle(CohesivePokemon* against);
};

#endif