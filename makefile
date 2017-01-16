CC=gcc
#CFLAGS=
LDFLAGS= -lmingw32 -lSDL2main -lSDL2 -lopengl32

all: run

2048.exe: src/main.c
	$(CC) $(CFLAGS) -o 2048.exe src/main.c $(LDFLAGS)

testSDL.exe: src/testSDL.c
	$(CC) $(CFLAGS) -o testSDL.exe src/testSDL.c $(LDFLAGS)

run: 2048.exe
	2048.exe
