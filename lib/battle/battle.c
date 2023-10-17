#include "../game/game.h"
#include "../menu/menu.h"
#include "../trainer/trainer.h"

void startBattle(Game* game, Trainer* against) {
  against->defeated = 1;
  game->battle.against = against;

  setStatus(game, "Battling a trainer");

  prepareMenu(MENU_TYPE_BATTLE, &game->menu);

  game->state = GAME_STATE_IN_MENU;
}