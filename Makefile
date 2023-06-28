SOURCES = main.cpp src/camera.cpp src/camera.hpp src/constants.hpp src/entities.cpp src/entities.hpp src/entity-background.cpp src/entity-background.hpp src/graphics.cpp src/graphics.hpp src/log.cpp src/log.hpp src/texture.cpp src/texture.hpp src/utils.cpp src/utils.hpp

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

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
