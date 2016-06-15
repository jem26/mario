all: main

main: main.h main.cpp
	g++ main.cpp -o main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -std=c++11

clean:
	rm main
