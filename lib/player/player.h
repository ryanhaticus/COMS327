#ifndef PLAYER_H
#define PLAYER_H

typedef class Game Game;

class Player {
 public:
  int x, y;
};

void createPlayer(Player *player, int x, int y);
int movePlayer(int move, Game *game);

#endif