all: build
	bin/main

graph_obj := obj/main.o
mech_obj  := obj/directions.o obj/map_wall.o obj/map_tile.o obj/game_map.o\
			 obj/player_piece.o obj/treasure.o obj/gamestate.o

$(mech_obj): obj/%.o: src/mechanics/sources/%.cpp src/mechanics/headers/%.h
	g++ -std=c++11 -Wall $< -c -o $@

$(graph_obj): obj/%.o: src/graphics/sources/%.cpp src/graphics/headers/*.h
	g++ -std=c++11 -Wall $< -c -o $@

build: $(mech_obj) $(graph_obj)
	g++ -std=c++11 $(mech_obj) $(graph_obj) -o bin/main -lncurses

style_check:
	python cpplint.py --filter=-legal/copyright,-build/include src/*/sources/*.cpp src/*/headers/*.h

clean:
	-rm obj/* bin/*
