all:
	g++ src/directions.cpp src/map_wall.cpp src/map_tile.cpp src/player.cpp \
		src/main.cpp \
		-std=gnu++11 -lncurses -o main
	./main

style_check:
	python cpplint.py --filter=-legal/copyright,-build/include src/*.cpp src/*.h

clean:
	rm main src/*.gch src/*.out
