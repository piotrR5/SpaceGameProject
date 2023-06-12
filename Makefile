SOURCES = main.cpp src/graphics.hpp src/game.hpp src/entities.hpp src/utils.hpp
LIBS = -lSDL2 -lSDL2_image -LSDL2_ttf

FLAGS = -Wall -Werror -Wno-error=maybe-uninitialized -Wno-error=unused-result -O3

OUT = SPACEGAME


all: clean
	g++ $(SOURCES) $(LIBS) -o $(OUT) $(FLAG)
prof: clean
	g++ $(SOURCES) $(LIBS) -o $(OUT) -pg $(FLAG)
	./$(OUT)
	gprof ./$(OUT) gmon.out > profOut.txt
	less profOut.txt
clean:
	rm -f profOut.txt $(OUT) gmon.out
run: all
	./$(OUT)
