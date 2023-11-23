#include "menu.h"

const char *menuHeaders[] = {"Trainer List", "Pokemon Center", "Pokemart",
                             "Battle", "Choose Starter Pokemon"};

#include <ncurses.h>

#include <cstdlib>
#include <cstring>

#include "../cohesivepokemon/cohesivepokemon.h"
#include "../game/game.h"
#include "../gamedata/gamedata.h"
#include "../room/room.h"
#include "../trainer/trainer.h"

void renderBaseMenu(const char *title) {
  int boxX = (WINDOW_WIDTH - MENU_WIDTH) / 2;
  int boxY = (WINDOW_HEIGHT - MENU_HEIGHT) / 2;

  int y, x;

  for (y = 0; y < MENU_HEIGHT; y++) {
    for (x = 0; x < MENU_WIDTH; x++) {
      if ((y == 0 || y == MENU_HEIGHT - 1) && (x == 0 || x == MENU_WIDTH - 1)) {
        mvaddch(boxY + y, boxX + x, '+');
        continue;
      }

      if (y == 0 || y == MENU_HEIGHT - 1) {
        mvaddch(boxY + y, boxX + x, '-');
        continue;
      }

      if (x == 0 || x == MENU_WIDTH - 1) {
        mvaddch(boxY + y, boxX + x, '|');
        continue;
      }

      mvaddch(boxY + y, boxX + x, ' ');
    }
  }

  mvprintw(boxY + 1, (WINDOW_WIDTH - strlen(title)) / 2, title);
}

void calculateStartPosition(int *x, int *y) {
  *x = (WINDOW_WIDTH - MENU_WIDTH) / 2 + 2;
  *y = (WINDOW_HEIGHT - MENU_HEIGHT) / 2 + 2;
}

void renderTrainerList(Game *game) {
  renderBaseMenu(menuHeaders[0]);

  int x, y;
  calculateStartPosition(&x, &y);

  Player *player = game->player;

  int j, i;
  int seen = 0;

  for (j = 0; j < ROOM_HEIGHT; j++) {
    for (i = 0; i < ROOM_WIDTH; i++) {
      if (y > MENU_HEIGHT) {
        return;
      }

      Trainer *trainer =
          game->map.rooms[game->map.y][game->map.x]->trainers[j][i];

      if (trainer == NULL) {
        continue;
      }

      if (seen < game->menu.position) {
        seen++;
        continue;
      }

      char name = getTrainerCharacter(trainer);

      int horizDist = player->x - i;
      int vertDist = player->y - j;

      mvprintw(y, x, "%c, %d %s and %d %s", name, abs(horizDist),
               horizDist > 0 ? "west" : "east", abs(vertDist),
               vertDist > 0 ? "north" : "south");
      y++;
    }
  }
}

int moveTrainerList(int move, Game *game) {
  switch (move) {
    case 27:  // Escape
      game->state = GAME_STATE_PLAYING;
      return 0;
    case KEY_UP:
      if (game->menu.position > 0) {
        game->menu.position--;
      }
      return 0;
    case KEY_DOWN:
      if (game->menu.position < game->map.trainersPerRoom - MENU_HEIGHT + 3) {
        game->menu.position++;
      }
      return 0;
  }

  return 1;
}

void renderPokemonCenter(Game *game) {
  renderBaseMenu(menuHeaders[1]);

  int x, y;
  calculateStartPosition(&x, &y);

  mvprintw(y + 1, x, "Your Pokemon were restored to full health!");
  mvprintw(y + 2, x, "Press < to exit.");

  for (int i = 0; i < game->player->pokemon.size(); i++) {
    game->player->pokemon[i]->HP = game->player->pokemon[i]->maxHP;
  }
}

int movePokemonCenter(int move, Game *game) {
  switch (move) {
    case '<':
      game->state = GAME_STATE_PLAYING;
      return 0;
  }

  return 1;
}

void renderPokemart(Game *game) {
  renderBaseMenu(menuHeaders[2]);

  int x, y;
  calculateStartPosition(&x, &y);

  mvprintw(y + 1, x, "Your supplies were replenished!");
  mvprintw(y + 2, x, "Press < to exit.");

  game->player->pokeballs = 10;
  game->player->potions = 3;
  game->player->revives = 3;
}

int movePokemart(int move, Game *game) {
  switch (move) {
    case '<':
      game->state = GAME_STATE_PLAYING;
      return 0;
  }

  return 1;
}

void renderBattle(Game *game) {
  renderBaseMenu(menuHeaders[3]);

  switch (game->battle->type) {
    case BATTLE_TYPE_TRAINER: {
      Trainer *against = game->battle->againstTrainer;

      int x, y;
      calculateStartPosition(&x, &y);

      mvprintw(y, x, "You are battling %c!", getTrainerCharacter(against));

      for (int i = 0; i < against->pokemon.size(); i++) {
        CohesivePokemon *pokemon = against->pokemon[i];

        mvprintw(y + i * 2, x,
                 "%s (Level %d): %d HP, %d Attack, %d Defense, %d Speed",
                 pokemon->identifier.c_str(), pokemon->getLevel(), pokemon->HP,
                 pokemon->attack, pokemon->defense, pokemon->speed);
        mvprintw(y + (i + 1) * 2 - 1, x, "Moves: %s, %s",
                 pokemon->moves[0].identifier.c_str(),
                 pokemon->moves[1].identifier.c_str());
      }

      break;
    }
    case BATTLE_TYPE_POKEMON: {
      CohesivePokemon *against = game->battle->againstPokemon;

      int x, y;
      calculateStartPosition(&x, &y);

      mvprintw(y, x, "You are battling a wild %s!",
               against->identifier.c_str());

      mvprintw(y + 2, x, "Level %d: %d HP, %d Attack, %d Defense, %d Speed",
               against->getLevel(), against->HP, against->attack,
               against->defense, against->speed);
      mvprintw(y + 3, x, "Moves: %s, %s", against->moves[0].identifier.c_str(),
               against->moves[1].identifier.c_str());

      break;
    }
  }
}

int moveBattle(int move, Game *game) {
  switch (move) {
    case 27:  // Escape
      game->state = GAME_STATE_PLAYING;
      return 0;
  }

  return 1;
}

void renderChooseStarter(Game *game) {
  renderBaseMenu(menuHeaders[4]);

  int x, y;
  calculateStartPosition(&x, &y);

  for (int i = 0; i < 3; i++) {
    mvprintw(y + i, x, "%d. %s", (i + 1),
             gameData->pokemon[game->player->possibleStarters[i]]
                 .identifier.c_str());
  }

  mvprintw(y + 5, x, "Choose your starter by hitting 1, 2, or 3!");
}

int moveChooseStarter(int move, Game *game) {
  switch (move) {
    case '1':
      game->player->pokemon.push_back(new CohesivePokemon(
          gameData->pokemon[game->player->possibleStarters[0]]));
      game->state = GAME_STATE_PLAYING;
      return 0;
    case '2':
      game->player->pokemon.push_back(new CohesivePokemon(
          gameData->pokemon[game->player->possibleStarters[1]]));
      game->state = GAME_STATE_PLAYING;
      return 0;
    case '3':
      game->player->pokemon.push_back(new CohesivePokemon(
          gameData->pokemon[game->player->possibleStarters[2]]));
      game->state = GAME_STATE_PLAYING;
      return 0;
  }

  return 1;
}

int prepareMenu(MenuType type, Menu *menu) {
  menu->type = type;
  menu->position = 0;

  switch (type) {
    case MENU_TYPE_TRAINER_LIST:
      menu->move = moveTrainerList;
      menu->render = renderTrainerList;
      break;
    case MENU_TYPE_POKEMON_CENTER:
      menu->move = movePokemonCenter;
      menu->render = renderPokemonCenter;
      break;
    case MENU_TYPE_POKEMART:
      menu->move = movePokemart;
      menu->render = renderPokemart;
      break;
    case MENU_TYPE_BATTLE:
      menu->move = moveBattle;
      menu->render = renderBattle;
      break;
    case MENU_TYPE_CHOOSE_STARTER:
      menu->move = moveChooseStarter;
      menu->render = renderChooseStarter;
      break;
  }

  return 0;
}