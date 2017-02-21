all:
	g++ src/screens.h src/main.cpp -std=gnu++11 -lncurses -o main
	./main

style_check:
	python cpplint.py --filter=-legal/copyright,-build/include src/*.cpp src/*.h

clean:
	rm main src/*.gch src/*.out
