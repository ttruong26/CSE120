CC=g++
CFLAGS=-std=c++11
# Define your source files here
SRCS=test.cpp TileGraph/TileGraph.cpp TileGraph/Tile.cpp Objects/Goal.cpp Objects/Line.cpp Objects/Workspace.cpp static/MapLoader.cpp
# Define your header files dependencies if needed for clarity or specific rules
DEPS=TileGraph/TileGraph.h TileGraph/Tile.h Objects/Goal.h Objects/Line.h Objects/Workspace.h static/MapLoader.h Objects/MapObject.h Utility.h

# Target to build the executable
test.exe: $(SRCS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)