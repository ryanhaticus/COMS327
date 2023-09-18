# Specify the default target to build when just running `make`
all: main

main: lib/tile/* lib/enemy/* lib/player/* lib/room/* lib/map/* lib/game/* util/queue/* main.c
	gcc lib/tile/tile.c lib/enemy/enemy.c lib/player/player.c lib/room/room.c lib/map/map.c util/queue/queue.c lib/game/game.c main.c -o main -Wall -Werror -lm

clean:
	rm -rf main *.o *.dSYM