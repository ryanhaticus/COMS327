#include "player.h"

#include <stdlib.h>

#include "../game/game.h"
#include "../menu/menu.h"
#include "../room/room.h"
#include "../trainer/trainer.h"

void createPlayer(Player *player, int x, int y) {
  player->x = x;
  player->y = y;
}

int canPlayerTravelTo(Player *player, Room *currentRoom, int x, int y) {
  if (currentRoom == NULL) {
    return 0;
  }

  int tileType = currentRoom->tiles[y][x].type;

  if (tileType == BOULDER || tileType == ENTRANCE || tileType == FOREST ||
      tileType == WATER) {
    return 0;
  }

  if (currentRoom->trainers[y][x] != NULL) {
    if (currentRoom->trainers[y][x]->defeated == 0) {
      return 2;
    }

    return 0;
  }

  return 1;
}

int movePlayer(int move, Game *game) {
  if (move == 'q' || move == 'Q') {
    game->state = GAME_STATE_QUIT;
    return 0;
  }

  if (game->state == GAME_STATE_IN_MENU) {
    return game->menu.move(move, game);
  }

  Room *currentRoom = game->map.rooms[game->map.y][game->map.x];
  Player *player = &game->player;

  if (game->state == GAME_STATE_PLAYING) {
    int dx = 0, dy = 0;
    switch (move) {
      case 't':
        setStatus(game, "Viewing Menu");
        prepareMenu(MENU_TYPE_TRAINER_LIST, &game->menu);
        game->state = GAME_STATE_IN_MENU;
        return 0;
      case '5':
      case ' ':
      case '.':
        return 0;
      case '7':
      case 'y':
        dx = -1;
        dy = -1;
        break;
      case '8':
      case 'k':
        dy = -1;
        break;
      case '9':
      case 'u':
        dx = 1;
        dy = -1;
        break;
      case '6':
      case 'l':
        dx = 1;
        break;
      case '3':
      case 'n':
        dx = 1;
        dy = 1;
        break;
      case '2':
      case 'j':
        dy = 1;
        break;
      case '1':
      case 'b':
        dx = -1;
        dy = 1;
        break;
      case '4':
      case 'h':
        dx = -1;
        break;
      case '>': {
        int tileType = currentRoom->tiles[player->y][player->x].type;
        if (tileType == POKEMON_CENTER || tileType == POKEMART) {
          game->state = GAME_STATE_IN_MENU;
          prepareMenu(tileType == POKEMON_CENTER ? MENU_TYPE_POKEMON_CENTER
                                                 : MENU_TYPE_POKEMART,
                      &game->menu);
          setStatus(game, "Viewing Menu");
          return 0;
        }
        break;
      }
    }

    if (dx != 0 || dy != 0) {
      int travelStatus = canPlayerTravelTo(player, currentRoom, player->x + dx,
                                           player->y + dy);

      if (travelStatus == 2) {
        startBattle(game,
                    currentRoom->trainers[player->y + dy][player->x + dx]);
        return 0;
      }

      if (travelStatus) {
        player->x += dx;
        player->y += dy;
        return 0;
      }
      setStatus(game, "Can't travel! Something is in the way.");
    }
  }

  return 1;
}
