CC=gcc
INCLUDE_MAC= -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -F/Library/Frameworks 
FRAMEWORK_MAC= -framework SDL2 -framework SDL2_ttf
FLAGS_WIN= -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lSDL2_ttf

2048: src/main.c src/move.c
	$(CC) -c -o obj/main.o src/main.c $(INCLUDE_MAC)
	$(CC) -c -o obj/move.o src/move.c $(INCLUDE_MAC)

	$(CC) -o bin/2048 obj/main.o obj/move.o $(INCLUDE_MAC) $(FRAMEWORK_MAC)

2048.exe: src/main.c src/move.c
	$(CC) -c -o obj/main.o src/main.c $(FLAGS_WIN)
	$(CC) -c -o obj/move.o src/move.c $(FLAGS_WIN)

	$(CC) -o bin/2048.exe obj/main.o obj/move.o $(FLAGS_WIN)

testSDL.exe: src/testSDL.c
	$(CC) -o testSDL.exe src/testSDL.c $(LDFLAGS)

mac: 2048
	./bin/2048

win: 2048.exe
	bin/2048.exe
