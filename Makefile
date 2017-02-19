all:
	g++ screens.h main.cpp -lncurses -o main
	./main
