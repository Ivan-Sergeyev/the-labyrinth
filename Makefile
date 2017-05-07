all: build
	bin/main

client_obj := obj/app.o obj/main.o
host_obj  := obj/directions.o obj/map_tile.o obj/map_wall.o obj/map.o \
			 obj/player.o obj/treasure.o obj/gamestate.o \
			 obj/host.o

$(host_obj): obj/%.o: src/host/sources/%.cpp src/host/headers/%.h
	g++ -std=c++11 -Wall $< -c -o $@

$(client_obj): obj/%.o: src/client/sources/%.cpp src/client/headers/*.h
	g++ -std=c++11 -Wall $< -c -o $@

build: $(host_obj) $(client_obj)
	g++ -std=c++11 $(host_obj) $(client_obj) -o bin/main -lncurses

style_check:
	python cpplint.py --filter=-legal/copyright,-build/include \
		src/*/sources/*.cpp src/*/headers/*.h

clean:
	-rm obj/* bin/* log.txt
