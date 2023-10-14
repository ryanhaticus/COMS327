all: main

main: tile.o trainer.o player.o room.o map.o game.o queue.o priorityqueue.o render.o menu.o main.o
	gcc tile.o trainer.o player.o room.o map.o game.o queue.o priorityqueue.o render.o menu.o main.o -o main -Wall -Werror -lm -lncurses

tile.o: ./lib/tile/tile.c ./lib/tile/tile.h
	gcc -c ./lib/tile/tile.c -o tile.o -Wall -Werror

trainer.o: ./lib/trainer/trainer.c ./lib/trainer/trainer.h
	gcc -c ./lib/trainer/trainer.c -o trainer.o -Wall -Werror

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

priorityqueue.o: ./util/priorityqueue/priorityqueue.c ./util/priorityqueue/priorityqueue.h
	gcc -c ./util/priorityqueue/priorityqueue.c -o priorityqueue.o -Wall -Werror

render.o: ./lib/render/render.c ./lib/render/render.h
	gcc -c ./lib/render/render.c -o render.o -Wall -Werror

menu.o: ./lib/menu/menu.c ./lib/menu/menu.h
	gcc -c ./lib/menu/menu.c -o menu.o -Wall -Werror

main.o: main.c
	gcc -c main.c -o main.o -Wall -Werror

clean:
	rm -rf main *.o *.dSYM