#include "menu.h"

const char *menuHeaders[] = {"Trainer List", "Pokemon Center", "Pokemart",
                             "Battle"};

#include <ncurses.h>

#include <cstdlib>
#include <cstring>

#include "../game/game.h"
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

  Player player = game->player;

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

      int horizDist = player.x - i;
      int vertDist = player.y - j;

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

void renderPokemonCenter(Game *game) { renderBaseMenu(menuHeaders[1]); }

int movePokemonCenter(int move, Game *game) {
  switch (move) {
    case '<':
      game->state = GAME_STATE_PLAYING;
      return 0;
  }

  return 1;
}

void renderPokemart(Game *game) { renderBaseMenu(menuHeaders[2]); }

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
  Trainer *against = game->battle.against;

  int x, y;
  calculateStartPosition(&x, &y);

  mvprintw(y, x, "You are battling %c!", getTrainerCharacter(against));
}

int moveBattle(int move, Game *game) {
  switch (move) {
    case 27:  // Escape
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
  }

  return 0;
}