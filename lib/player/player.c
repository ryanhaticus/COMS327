#include "player.h"

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../room/room.h"

void createPlayer(struct Player *player, int x, int y) {
  player->x = x;
  player->y = y;
}