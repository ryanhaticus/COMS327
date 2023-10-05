# Ryan Huellen's Pokemon Game

Welcome to Ryan Huellen's Pokemon Game! This is a rogue-like text-based game written in C, heavily inspired by the Pokemon franchise. Players will embark on an adventure, capturing and battling creatures in a procedurally generated world.

## Table of Contents

1. Features
2. Building the Project
3. Trainers
4. Controls

## Features

- Procedurally generated world with various region types, Pokemon Centers, and Pokemarts.
- Upon entering a room, your player character '@' is placed on the path
- 6 types of trainers exist. We have Hikers, Rivals, Pacers, Wanderers, Sentries, and Explorers.

## Trainers

### Hikers and Rivals

Hikers and Rivals follow an efficient path to the player based on their respective cost maps.

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

In this iteration, the player cannot be controlled and the player cannot move rooms. Instead, we observe the priority queue driven movement of the various trainers.
