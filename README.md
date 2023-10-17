# Ryan Huellen's Pokemon Game

Welcome to Ryan Huellen's Pokemon Game! This is a rogue-like text-based game written in C, heavily inspired by the Pokemon franchise. Players will embark on an adventure, capturing and battling creatures in a procedurally generated world.

## Table of Contents

1. Features
2. Building the Project
3. Trainers
4. Controls
5. Buildings

## Features

- Procedurally generated world with various region types, Pokemon Centers, and Pokemarts.
- Upon entering a room, your player character '@' is placed on the path
- 6 types of trainers exist. We have Hikers, Rivals, Pacers, Wanderers, Sentries, and Explorers.
- Ability to choose how many trainers spawn in.
- Player movement in all eight directions (north west, north, north east, east, south east, south, south west, west)
- Battle interface
- Pokemart interface
- Pokemon Center interface
- Trainer interface

## Trainers

In order to pick the number of trainers that spawn on the map, you can run the binary with the `--numtrainers` flag. Here's a sample of choosing 7 trainers:

`./main --numtrainers 7`

### Trainer Interface

In order to open the trainer interface, you can hit `t`. To close this interface, you can hit `escape`. The trainer interface will report the nearby Pokemon along with their locations relative to the player. In order to scroll through the Pokemon list, you can use `up arrow` and `down arrow`. Please note, opening the trainer interface uses a turn!

### Trainer Battles

All trainers are undefeated when they initially spawn. When you move into a trainer's tile or a trainer moves in your tile, a battle is initiated. At this time, battles do not have any gameplay mechanics. You can simply hit `escape` to exit. After doing so, the respective trainer becomes defeated.

### Hikers and Rivals

Hikers and Rivals follow an efficient path to the player based on their respective cost maps. Note that if there is no valid path to the player as that player is blocked by other trainers or immovable terrain, then hikers and rivals will not move. Moreover, if a Hiker or Rival is defeated, they will instead choose to move in a random direction, rather than pathing to the player.

### Pacers

Pacers choose a single direction and move in that direction until they hit an immovable object. Then, they turn around and repeat.

### Wanderers

Wanderers move in a random directon and continue that direction until they reach the end of their current terrain type. Then, they pick another direction to stay within the terrain limits.

### Explorers

Explorers move like wanderers, except they can leave the current terrain type.

### Sentries

Sentries don't move at all! Be wary!

## Building the Project

- To build the project, simply run `make`. This will generate a variety of output files, along with the executable `main`.
- To run the project, open a terminal and type `./main`.

## Controls

The game features a variety of controls. Building or interface specific controls can be found in their respective sections as well as in the following list.

- `Q` or `q` to quit.
- `7` or `y` to move to the north west.
- `8` or `k` to move north.
- `6` or `l` to move east.
- `3` or `n` to move south east.
- `2` or `j` to move south.
- `1` or `b` to move south west.
- `4` or `h` to move left.
- `>` to open a Pokemon Center or Pokemart interface (requires standing on the respective tile).
- `<` to close a Pokemon Center or Pokemart interface.
- `5` or `space` or `.` to rest for a turn.
- `t` to display a list of trainers.
- `escape` to exit any interface.
- `up arrow` to navigate in certain interfaces.
- `down arrow` to navigate in certain interfaces.

## Buildings

The game features two buildings, a Pokemon Center (C) and a Pokemart (M). Upon pathing to a respective building, you can open the building's interface with the `>` key. In order to close the interface, press the `<` key. In the future, you'll be able to buy power ups and items in these two buildings.
