# Ryan Huellen's Pokemon Game

Welcome to Ryan Huellen's Pokemon Game! This is a rogue-like text-based game written in C, heavily inspired by the Pokemon franchise. Players will embark on an adventure, capturing and battling creatures in a procedurally generated world.

## Table of Contents

1. Features
2. Building the Project
3. Controls

## Features

- Procedurally generated world with various region types, Pokemon Centers, and Pokemarts.
- Ability to travel between rooms in a 401x401 map (each room is 80x21)
- Coordinate display, along with the current seed
- Display of a cost map for two enemy types, Hiker and Rival, to travel towards the player
- Upon entering a room, your player character '@' is placed on a random entrance

## Building the Project

- To build the project, simply run `make`. This will generate a variety of output files, along with the executable `main`.
- To run the project, open a terminal and type `./main`.

## Controls

The game is command based. In other words, you have the opportunity to enter one command each time the game "loops". The available commands are as follows:

1. n - travel one room north
2. e - travel one room east
3. s - travel one room south
4. w - travel one room west
5. f x y - travel to room located at map coordinates (x,y)
