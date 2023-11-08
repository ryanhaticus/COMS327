#include "../game/game.h"
#include "../menu/menu.h"
#include "../trainer/trainer.h"

void Battle::startTrainerBattle(Trainer* against) {
  against->defeated = 1;
  this->againstTrainer = against;
  this->type = BATTLE_TYPE_TRAINER;

  setStatus(game, "Battling a trainer");

  prepareMenu(MENU_TYPE_BATTLE, &game->menu);

  game->state = GAME_STATE_IN_MENU;
}

void Battle::startPokemonBattle(CohesivePokemon* against) {
  this->againstPokemon = against;
  this->type = BATTLE_TYPE_POKEMON;

  setStatus(game, "Battling a wild pokemon");

  prepareMenu(MENU_TYPE_BATTLE, &game->menu);

  game->state = GAME_STATE_IN_MENU;
}