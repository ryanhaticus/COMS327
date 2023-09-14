#include "game.h"

#include <stdio.h>
#include <stdlib.h>

int createGame(struct Game *game) {
  createMap(&game->map);

  return 0;
}

int destroyGame(struct Game *game) {
  destroyMap(&game->map);

  return 0;
}

void renderGame(struct Game *game) {
  printf("\e[1;1H\e[2J");
  printf("❮ Map Location: (%d, %d) ❯\n", game->map.x - 200, game->map.y - 200);
  renderMap(&game->map);
  printf(
      "❮ Enter `n`, `s`, `e`, `w`, or `f x y` to move rooms. Enter `q` to "
      "quit. ❯\n");
}

void startLoop(struct Game *game) {
  char cmd;
  char input[MAX_INPUT_SIZE];
  int y, x;

  renderGame(game);

  while (1) {
    fgets(input, MAX_INPUT_SIZE, stdin);

    int numInputs = sscanf(input, "%c %d %d", &cmd, &x, &y);

    if (cmd == 'q') {
      break;
    }

    switch (cmd) {
      case 'n':
        game->map.y = game->map.y - 1 < 0 ? 0 : game->map.y - 1;
        break;
      case 's':
        game->map.y =
            game->map.y + 1 >= MAP_HEIGHT ? MAP_HEIGHT - 1 : game->map.y + 1;
        break;
      case 'e':
        game->map.x =
            game->map.x + 1 >= MAP_WIDTH ? MAP_WIDTH - 1 : game->map.x + 1;
        break;
      case 'w':
        game->map.x = game->map.x - 1 < 0 ? 0 : game->map.x - 1;
        break;
      case 'f':
        if (numInputs != 3) {
          break;
        }
        if (x < -200 || x > 200 || y < -200 || y > 200) {
          break;
        }

        game->map.x = x + 200;
        game->map.y = y + 200;
        break;
      default:
        break;
    }

    struct Room *room = game->map.rooms[game->map.y][game->map.x];

    if (room == NULL) {
      room = malloc(sizeof(struct Room));
      game->map.rooms[game->map.y][game->map.x] = room;
      createRoom(&game->map, room, game->map.x, game->map.y);
    }

    renderGame(game);
  }
}