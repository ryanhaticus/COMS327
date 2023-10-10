#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
  int x, y;
} Player;

void createPlayer(Player *player, int x, int y);

#endif