#ifndef TRAINER_H
#define TRAINER_H

#include "../player/player.h"
#include "../room/room.h"
#include "../tile/tile.h"

typedef struct Room Room;

#define NUM_TRAINERS 6

enum TrainerType { HIKER, RIVAL, PACER, WANDERER, SENTRY, EXPLORER };

typedef struct Trainer {
  enum TrainerType type;
  int x, y;
  int dir;
} Trainer;

int getTrainerTileCost(Trainer *trainer, Room *room, Tile *tile);
void getTrainerTravelCost(int costs[ROOM_HEIGHT][ROOM_WIDTH], Room *room,
                          Trainer *trainer, Player *player);
void placeTrainerInRoom(Trainer *trainersInRoom[ROOM_HEIGHT][ROOM_WIDTH],
                        Trainer *trainer, Room *room);
char getTrainerCharacter(Trainer *trainer);
int createTrainer(Trainer **trainer);
void destroyTrainer(Trainer *trainer);
void moveTrainers(Room *room, Player *player);

#endif