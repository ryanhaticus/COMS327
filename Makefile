all: main

main: tile.o enemy.o player.o room.o map.o game.o queue.o fibheap.o main.o
	gcc tile.o enemy.o player.o room.o map.o game.o queue.o fibheap.o main.o -o main -Wall -Werror -lm

tile.o: ./lib/tile/tile.c ./lib/tile/tile.h
	gcc -c ./lib/tile/tile.c -o tile.o -Wall -Werror

enemy.o: ./lib/enemy/enemy.c ./lib/enemy/enemy.h
	gcc -c ./lib/enemy/enemy.c -o enemy.o -Wall -Werror

player.o: ./lib/player/player.c ./lib/player/player.h
	gcc -c ./lib/player/player.c -o player.o -Wall -Werror

room.o: ./lib/room/room.c ./lib/room/room.h
	gcc -c ./lib/room/room.c -o room.o -Wall -Werror

map.o: ./lib/map/map.c ./lib/map/map.h
	gcc -c ./lib/map/map.c -o map.o -Wall -Werror

game.o: ./lib/game/game.c ./lib/game/game.h
	gcc -c ./lib/game/game.c -o game.o -Wall -Werror

queue.o: ./util/queue/queue.c ./util/queue/queue.h
	gcc -c ./util/queue/queue.c -o queue.o -Wall -Werror

fibheap.o: ./util/fibheap/fibheap.c ./util/fibheap/fibheap.h
	gcc -c ./util/fibheap/fibheap.c -o fibheap.o -Wall -Werror

main.o: main.c
	gcc -c main.c -o main.o -Wall -Werror

clean:
	rm -rf main *.o *.dSYM