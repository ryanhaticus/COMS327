#ifndef TRAINER_H
#define TRAINER_H

#include "../room/room.h"

typedef struct Room Room;
typedef struct Player Player;
typedef struct Tile Tile;

#define NUM_TRAINERS 6

enum TrainerType { HIKER, RIVAL, PACER, WANDERER, SENTRY, EXPLORER };

typedef struct Trainer {
  enum TrainerType type;
  int x, y;
  int dir;
  int defeated;
} Trainer;

int getTrainerTileCost(Trainer *trainer, Room *room, Tile *tile);
void getTrainerTravelCost(int costs[ROOM_HEIGHT][ROOM_WIDTH], Room *room,
                          Trainer *trainer, Player *player);
void placeTrainerInRoom(Trainer *trainersInRoom[ROOM_HEIGHT][ROOM_WIDTH],
                        Trainer *trainer, Room *room);
char getTrainerCharacter(Trainer *trainer);
int createTrainer(Trainer **trainer);
void destroyTrainer(Trainer *trainer);
void moveTrainers(Room *room, Player *player, Trainer **trainerToBattle);

#endif