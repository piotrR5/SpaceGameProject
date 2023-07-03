ENGINE_SOURCES = main.cpp src/engine/Engine.cpp src/engine/Engine.hpp src/engine/utils/log.cpp src/engine/utils/log.hpp src/engine/utils/sg_math.cpp src/engine/utils/sg_math.hpp src/engine/utils/config.hpp src/engine/utils/keyStateMapInit.cpp src/engine/utils/keyStateMapInit.hpp src/engine/rendering/texture.cpp src/engine/rendering/texture.hpp src/engine/rendering/render.cpp src/engine/rendering/render.hpp src/engine/rendering/handleCamera.cpp src/engine/rendering/handleCamera.hpp

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

FLAGS = -Wall -Werror -Wno-error=maybe-uninitialized -Wno-error=unused-result -O3

OUT = SPACEGAME


all: clean
	g++ $(ENGINE_SOURCES) $(LIBS) -o $(OUT) $(FLAG)
prof: clean
	g++ $(ENGINE_SOURCES) $(LIBS) -o $(OUT) -pg $(FLAG)
	./$(OUT)
	gprof ./$(OUT) gmon.out > profOut.txt
	less profOut.txt
clean:
	rm -f profOut.txt $(OUT) gmon.out
run: all
	./$(OUT)
