#ifndef BATTLE_H
#define BATTLE_H

typedef class Trainer Trainer;
typedef class Game Game;

class Battle {
 public:
  Trainer* against;
};

void startBattle(Game* game, Trainer* against);

#endif