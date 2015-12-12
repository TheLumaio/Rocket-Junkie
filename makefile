CC = clang++
CFLAGS = -static-libgcc -std=c++14 -O0 -include-pch .stdafx.c++.pch
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system -lthor
SOURCES = main.cpp engine.cpp menustate.cpp gamestate.cpp resourcemanager.cpp gameserver.cpp gameclient.cpp chatbox.cpp board.cpp

code:
	$(CC) -o "Rocket_Junkie.exe" $(CFLAGS) $(SOURCES) $(LDFLAGS)
	move "Rocket_Junkie.exe" ../build/
	