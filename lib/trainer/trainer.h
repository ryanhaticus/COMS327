#include "../game/game.h"
#include "../room/room.h"
#include "../tile/tile.h"

#ifndef TRAINER_H
#define TRAINER_H

enum TrainerType { HIKER, RIVAL };

struct Trainer {
  enum TrainerType type;
  int x, y;
};

struct Room;

int getTrainerTileCost(struct Trainer *trainer, struct Tile *tile);
void getTrainerTravelCost(int costs[ROOM_HEIGHT][ROOM_WIDTH], struct Room *room,
                          struct Trainer *trainer, int endX, int endY);
void printTrainerTravelCost(struct Game *game, enum TrainerType type);

#endif