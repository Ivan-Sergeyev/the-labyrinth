all: bin/main 
	bin/main


graph_obj := obj/main.o
mech_obj  := obj/directions.o obj/gamestate.o obj/map_tile.o obj/map_wall.o obj/player.o obj/treasure.o

$(mech_obj): obj/%.o: src/mechanics/sources/%.cpp src/mechanics/headers/%.h
	g++ -Wall $< -c -o $@

$(graph_obj): obj/%.o: src/graphics/sources/%.cpp src/graphics/headers/*.h
	g++ -Wall $< -c -o $@

bin/main: $(mech_obj) $(graph_obj)
	g++ $(mech_obj) $(graph_obj) -o bin/main -lncurses

style_check:
	python cpplint.py --filter=-legal/copyright,-build/include src/*/sourcses/*.cpp src/*/headers/*.h

clean:
	rm obj/* bin/*
