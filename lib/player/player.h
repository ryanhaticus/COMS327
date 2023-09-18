#ifndef PLAYER_H
#define PLAYER_H

struct Player {
  int x, y;
};

void createPlayer(struct Player *player, int x, int y);

#endif