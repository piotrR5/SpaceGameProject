ENGINE = src/engine/globals.hpp src/engine/Engine.cpp src/engine/eventHandlers.cpp src/engine/Engine.hpp

GUI = src/engine/gui/gui.cpp src/engine/gui/gui.hpp

RENDERING = src/engine/rendering/texture.cpp src/engine/rendering/texture.hpp src/engine/rendering/render.cpp src/engine/rendering/render.hpp src/engine/rendering/handleCamera.cpp src/engine/rendering/handleCamera.hpp src/engine/rendering/text.cpp src/engine/rendering/text.hpp

UTILS = src/engine/utils/sg_math.cpp src/engine/utils/sg_math.hpp src/engine/utils/log.cpp src/engine/utils/log.hpp src/engine/utils/config.hpp

GAME = src/game/entity-vessel.hpp src/game/entity-vessel.cpp src/game/entity-planet.hpp src/game/entity-planet.cpp src/game/entity-projectile.hpp src/game/entity-projectile.cpp src/game/objectHandler.hpp src/game/objectHandler.cpp src/game/movement-battle.cpp src/game/objects.hpp src/game/objects.cpp

MAIN = main.cpp

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

FLAGS = -Wall -Werror -Wno-error=maybe-uninitialized -Wno-error=unused-result -O3

OUT = SPACEGAME


all: clean
	g++ $(MAIN) $(ENGINE) $(RENDERING) $(UTILS) $(GAME) $(GUI) $(LIBS) -g -o $(OUT) $(FLAG)
prof: clean
	g++ $(MAIN) $(ENGINE) $(RENDERING) $(UTILS) $(GAME) $(GUI) $(LIBS) -g -o $(OUT) -pg $(FLAG)
	./$(OUT)
	gprof ./$(OUT) gmon.out > profOut.txt
	less profOut.txt
clean:
	rm -f profOut.txt $(OUT) gmon.out
run: all
	./$(OUT)
