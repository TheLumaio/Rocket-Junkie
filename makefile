CC = clang++
CFLAGS = -std=c++14 -O0
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system -lthor
SOURCES = main.cpp engine.cpp menustate.cpp gamestate.cpp resourcemanager.cpp gameserver.cpp gameclient.cpp

code:
	$(CC) -o "Rocket_Junkie.exe" $(SOURCES) $(CFLAGS) $(LDFLAGS)
	move "Rocket_Junkie.exe" ../build/
	