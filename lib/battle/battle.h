#ifndef BATTLE_H
#define BATTLE_H

typedef struct Trainer Trainer;
typedef struct Game Game;

typedef struct Battle {
  Trainer* against;
} Battle;

void startBattle(Game* game, Trainer* against);

#endif