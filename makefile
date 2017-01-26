CC=gcc
FLAGS= -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lSDL2_ttf -lSDL2_image

all: 2048.exe

run: 2048.exe
	2048.exe

obj/main.o: src/main.c
	$(CC) -c -o obj/main.o src/main.c $(FLAGS)
obj/move.o: src/move.c
	$(CC) -c -o obj/move.o src/move.c $(FLAGS)
obj/highscore.o: src/highscore.c
	$(CC) -c -o obj/highscore.o src/highscore.c $(FLAGS)
obj/init.o: src/init.c
	$(CC) -c -o obj/init.o src/init.c $(FLAGS)
obj/update.o: src/update.c
	$(CC) -c -o obj/update.o src/update.c $(FLAGS)
obj/startup.o: src/startup.c
	$(CC) -c -o obj/startup.o src/startup.c $(FLAGS)

2048.exe: obj/main.o obj/move.o obj/highscore.o obj/init.o obj/update.o obj/startup.o
	$(CC) -o 2048.exe obj/main.o obj/move.o obj/highscore.o obj/init.o obj/update.o obj/startup.o $(FLAGS)
