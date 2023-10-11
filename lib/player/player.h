#ifndef PLAYER_H
#define PLAYER_H

typedef struct Game Game;

typedef struct Player {
  int x, y;
} Player;

void createPlayer(Player *player, int x, int y);
int movePlayer(int move, Game *game);

#endif