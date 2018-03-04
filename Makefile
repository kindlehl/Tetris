
all: main game block tetromino 
	g++ main.o game.o block.o tetromino.o -I/usr/include -o Tetris -lSDL2 -lsdl_utils 
debug: main game block utils tetromino 
	g++ -D DEBUG main.o game.o block.o sdl_utils.o tetromino.o -I/usr/include -o prog -lSDL2

main:
	g++ -c main.cpp -I/usr/include -o main.o -lSDL2 -lsdl_utils
game:
	g++ -c game.cpp -I/usr/include -o game.o -lSDL2
block:
	g++ -c block.cpp -I/usr/include -o block.o -lSDL2
#utils:
#	g++ -c sdl_utils.cpp -I/usr/include -o sdl_utils.o -lSDL2
tetromino:
	g++ -c tetromino.cpp -I/usr/include -o tetromino.o -lSDL2

clean:
	rm *.o
