ENGINE = src/engine/globals.hpp src/engine/Engine.cpp src/engine/eventHandlers.cpp src/engine/Engine.hpp

GUI = src/engine/gui/gui.cpp src/engine/gui/gui.hpp

RENDERING = src/engine/rendering/texture.cpp src/engine/rendering/texture.hpp src/engine/rendering/render.cpp src/engine/rendering/render.hpp src/engine/rendering/handleCamera.cpp src/engine/rendering/handleCamera.hpp src/engine/rendering/text.cpp src/engine/rendering/text.hpp

UTILS = src/engine/utils/sg_math.cpp src/engine/utils/sg_math.hpp src/engine/utils/log.cpp src/engine/utils/log.hpp src/engine/utils/config.hpp

MAIN = main.cpp

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

FLAGS = -Wall -Werror -Wno-error=maybe-uninitialized -Wno-error=unused-result -O3

OUT = SPACEGAME


all: clean
	g++ $(MAIN) $(ENGINE) $(RENDERING) $(UTILS) $(GUI) $(LIBS) -o $(OUT) $(FLAG)
prof: clean
	g++ $(MAIN) $(ENGINE) $(RENDERING) $(UTILS) $(GUI) $(LIBS) -o $(OUT) -pg $(FLAG)
	./$(OUT)
	gprof ./$(OUT) gmon.out > profOut.txt
	less profOut.txt
clean:
	rm -f profOut.txt $(OUT) gmon.out
run: all
	./$(OUT)
