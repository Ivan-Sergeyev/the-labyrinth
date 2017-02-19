all:
	g++ screens.h main.cpp -lncurses -o main
	./main

style_check:
	python cpplint.py --filter=-legal/copyright,-build/include *.cpp *.h

clean:
	rm main *.gch
