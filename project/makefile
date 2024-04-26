CC=g++
CFLAGS=-std=c++14
# Define your source files here
SRCS=test.cpp graph/TileGraph.cpp graph/Tile.cpp Objects/Robot.cpp Objects/Goal.cpp Objects/Line.cpp Objects/Data.cpp Objects/Workspace.cpp static/MapLoader.cpp Objects/MapObject.cpp
# Define your header files dependencies if needed for clarity or specific rules
DEPS=graph/TileGraph.h graph/Tile.h Objects/Robot.h Objects/Goal.h Objects/Line.h Objects/Workspace.h Objects/Data.h static/MapLoader.h Objects/MapObject.h include/Utility.h

# Target to build the executable
test.exe: $(SRCS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

g