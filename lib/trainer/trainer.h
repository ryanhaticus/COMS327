#ifndef TRAINER_H
#define TRAINER_H

#include "../room/room.h"

typedef class Room Room;
typedef class Player Player;
typedef class Tile Tile;

#define NUM_TRAINERS 6

enum TrainerType { HIKER, RIVAL, PACER, WANDERER, SENTRY, EXPLORER };

class Trainer {
 public:
  enum TrainerType type;
  int x, y;
  int dir;
  int defeated;
};

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