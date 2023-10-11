#include "player.h"

#include "../game/game.h"

void createPlayer(Player *player, int x, int y) {
  player->x = x;
  player->y = y;
}

int movePlayer(int move, Game *game) {
  if (move == 'q') {
    game->state = GAME_STATE_QUIT;
    return 0;
  }

  if (game->state == GAME_STATE_IN_MENU) {
    switch (move) {
      case 't':
        break;
      case 65:  // up arrow
        break;
      case 66:  // down arrow
        break;
      case 27:  // escape
        break;
    }

    return 1;
  }

  if (game->state == GAME_STATE_PLAYING) {
    switch (move) {
      case '5':
      case ' ':
      case '.':
        break;
      case '7':
      case 'y':
        break;
      case '8':
      case 'k':
        break;
      case '9':
      case 'u':
        break;
      case '6':
      case 'l':
        break;
      case '3':
      case 'n':
        break;
      case '2':
      case 'j':
        break;
      case '1':
      case 'b':
        break;
      case '4':
      case 'h':
        break;
      case '>':
        break;
    }
  }

  return 1;
}