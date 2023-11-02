CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -I/opt/homebrew/Cellar/sdl2/2.28.3/include
LIBS = -L/opt/homebrew/Cellar/sdl2/2.28.3/lib -lSDL2

main: src/main.c
	$(CC) $(CFLAGS) -o build/main src/main.c $(LIBS) && make run

clean:
	rm -f ./build/main

run:
	./build/main