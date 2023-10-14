#include "player.h"

#include <stdlib.h>

#include "../game/game.h"
#include "../menu/menu.h"
#include "../room/room.h"

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
    return 0;
  }

  return 1;
}

int movePlayer(int move, Game *game) {
  if (move == 'q') {
    game->state = GAME_STATE_QUIT;
    return 0;
  }

  if (game->state == GAME_STATE_IN_MENU) {
    switch (move) {
      case '<':
      case 27:  // escape
        game->state = GAME_STATE_PLAYING;
        return 0;
      default:
        return game->menu.move(move, game);
    }

    return 1;
  }

  Room *currentRoom = game->map.rooms[game->map.y][game->map.x];
  Player *player = &game->player;

  if (game->state == GAME_STATE_PLAYING) {
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
        if (canPlayerTravelTo(player, currentRoom, player->x - 1,
                              player->y - 1)) {
          player->x--;
          player->y--;
          return 0;
        }
        setStatus(game, "Can't travel to upper left! Something is in the way.");
        break;
      case '8':
      case 'k':
        if (canPlayerTravelTo(player, currentRoom, player->x, player->y - 1)) {
          player->y--;
          return 0;
        }
        setStatus(game, "Can't travel up! Something is in the way.");
        break;
      case '9':
      case 'u':
        if (canPlayerTravelTo(player, currentRoom, player->x + 1,
                              player->y - 1)) {
          player->x++;
          player->y--;
          return 0;
        }
        setStatus(game,
                  "Can't travel to upper right! Something is in the way.");
        break;
      case '6':
      case 'l':
        if (canPlayerTravelTo(player, currentRoom, player->x + 1, player->y)) {
          player->x++;
          return 0;
        }
        setStatus(game, "Can't travel right! Something is in the way.");
        break;
      case '3':
      case 'n':
        if (canPlayerTravelTo(player, currentRoom, player->x + 1,
                              player->y + 1)) {
          player->x++;
          player->y++;
          return 0;
        }
        setStatus(game,
                  "Can't travel to lower right! Something is in the way.");
        break;
      case '2':
      case 'j':
        if (canPlayerTravelTo(player, currentRoom, player->x, player->y + 1)) {
          player->y++;
          return 0;
        }
        setStatus(game, "Can't travel down! Something is in the way.");
        break;
      case '1':
      case 'b':
        if (canPlayerTravelTo(player, currentRoom, player->x - 1,
                              player->y + 1)) {
          player->x--;
          player->y++;
          return 0;
        }
        setStatus(game, "Can't travel to lower left! Something is in the way.");
        break;
      case '4':
      case 'h':
        if (canPlayerTravelTo(player, currentRoom, player->x - 1, player->y)) {
          player->x--;
          return 0;
        }
        setStatus(game, "Can't travel left! Something is in the way.");
        break;
      case '>': {
        int tileType = game->map.rooms[game->map.y][game->map.x]
                           ->tiles[player->y][player->x]
                           .type;
        if (tileType == POKEMON_CENTER) {
          game->state = GAME_STATE_IN_MENU;
          prepareMenu(MENU_TYPE_POKEMON_CENTER, &game->menu);
          setStatus(game, "Viewing Menu");
          return 0;
        }

        if (tileType == POKEMART) {
          game->state = GAME_STATE_IN_MENU;
          prepareMenu(MENU_TYPE_POKEMART, &game->menu);
          setStatus(game, "Viewing Menu");
          return 0;
        }
        break;
      }
    }
  }

  return 1;
}