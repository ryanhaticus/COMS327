#ifndef TRAINER_H
#define TRAINER_H

#include "../game/game.h"
#include "../player/player.h"
#include "../room/room.h"
#include "../tile/tile.h"

#define NUM_TRAINERS 6

enum TrainerType { HIKER, RIVAL, PACER, WANDERER, SENTRY, EXPLORER };

struct Trainer {
  enum TrainerType type;
  int x, y;
  int dir;  // N = 0, E = 1, S = 2, W = 3
};

struct Room;

int getTrainerTileCost(struct Trainer *trainer, struct Room *room,
                       struct Tile *tile);
void getTrainerTravelCost(int costs[ROOM_HEIGHT][ROOM_WIDTH], struct Room *room,
                          struct Trainer *trainer, struct Player *player);
void placeTrainerInRoom(struct Trainer *trainersInRoom[ROOM_HEIGHT][ROOM_WIDTH],
                        struct Trainer *trainer, struct Room *room);
char getTrainerCharacter(struct Trainer *trainer);
int createTrainer(struct Trainer **trainer);
void destroyTrainer(struct Trainer *trainer);
void moveTrainers(struct Room *room, struct Player *player);

#endif