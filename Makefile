all: main

main: tile.o trainer.o player.o room.o map.o game.o queue.o priorityqueue.o render.o menu.o battle.o main.o
	g++ tile.o trainer.o player.o room.o map.o game.o queue.o priorityqueue.o render.o menu.o battle.o main.o -o main -Wall -Werror -lm -lncurses

tile.o: ./lib/tile/tile.cpp ./lib/tile/tile.h
	g++ -c ./lib/tile/tile.cpp -o tile.o -Wall -Werror

trainer.o: ./lib/trainer/trainer.cpp ./lib/trainer/trainer.h
	g++ -c ./lib/trainer/trainer.cpp -o trainer.o -Wall -Werror

player.o: ./lib/player/player.cpp ./lib/player/player.h
	g++ -c ./lib/player/player.cpp -o player.o -Wall -Werror

room.o: ./lib/room/room.cpp ./lib/room/room.h
	g++ -c ./lib/room/room.cpp -o room.o -Wall -Werror

map.o: ./lib/map/map.cpp ./lib/map/map.h
	g++ -c ./lib/map/map.cpp -o map.o -Wall -Werror

game.o: ./lib/game/game.cpp ./lib/game/game.h
	g++ -c ./lib/game/game.cpp -o game.o -Wall -Werror

queue.o: ./util/queue/queue.c ./util/queue/queue.h
	g++ -x c -c ./util/queue/queue.c -o queue.o -Wall -Werror

priorityqueue.o: ./util/priorityqueue/priorityqueue.c ./util/priorityqueue/priorityqueue.h
	g++ -x c -c ./util/priorityqueue/priorityqueue.c -o priorityqueue.o -Wall -Werror

render.o: ./lib/render/render.cpp ./lib/render/render.h
	g++ -c ./lib/render/render.cpp -o render.o -Wall -Werror

menu.o: ./lib/menu/menu.cpp ./lib/menu/menu.h
	g++ -c ./lib/menu/menu.cpp -o menu.o -Wall -Werror

battle.o: ./lib/battle/battle.cpp ./lib/battle/battle.h
	g++ -c ./lib/battle/battle.cpp -o battle.o -Wall -Werror

main.o: main.cpp
	g++ -c main.cpp -o main.o -Wall -Werror

clean:
	rm -rf main *.o *.dSYM