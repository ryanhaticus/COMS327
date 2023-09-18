# Changelog

09/07/2023, 11:09 AM: Initialized project (main.c, CHANGELOG.md, README.md, Makefile)
09/08/2023, 1:42 PM: Created main game structures (game, map, room, tile)
09/10/2023, 3:33 PM: Added custom queue util. and core room population method
09/11/2023, 11:24 PM: Added roads, once again, with better clarity
09/12/2023, 10:32 AM: Recreated path algorithm
09/12/2023, 12:05 PM: Dynamic allocation for rooms. Avoiding the creation of a room unless we're visitng it.
09/12/2023, 6:23 PM: Added the game loop
09/12/2023, 8:55 PM: Finished reading input with `fgets` and parsing with `sscanf`
09/12/2023, 9:05 PM: Finalized moving between rooms on the map
09/12/2023, 10:33 PM: Made Pokemon Center and Pokemart. Also ensured probability is based on distance from center
09/17/2023, 6:30 PM: Created Player struct and appended the memory to the Game struct
09/17/2023, 8:22 PM: Centralized rendering logic after repeated attempts to replace a terminal character in place failed
09/17/2023, 8:30 PM: Displaying the seed in the terminal header
09/17/2023, 8:47 PM: Implemented Enemy struct and Hiker/Rival tile cost functions
