all:
	g++ title_screen.h main.cpp -lncurses -o main
	./main
