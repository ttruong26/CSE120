cmake_minimum_required(VERSION 3.13)
project(UCM_Project VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include_directories(
#     ${CMAKE_CURRENT_SOURCE_DIR}/static
#     ${CMAKE_CURRENT_SOURCE_DIR}/graph
#     ${CMAKE_CURRENT_SOURCE_DIR}/Objects
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )

set(UCM_SOURCES 
    test.cpp
    graph/TileGraph.cpp
    graph/Tile.cpp
    Objects/Robot.cpp 
    Objects/Goal.cpp 
    Objects/Line.cpp 
    Objects/Data.cpp 
    Objects/Workspace.cpp 
    static/MapLoader.cpp 
    Objects/MapObject.cpp
)

set(UCM_HEADERS 
    graph/TileGraph.h
    graph/Tile.h
    include/Utility.h
    Objects/Robot.h 
    Objects/Goal.h 
    Objects/Line.h 
    Objects/Data.h 
    Objects/Workspace.h 
    static/MapLoader.h 
    Objects/MapObject.h
)

# add_executable(test ${UCM_SOURCES})


# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/mapfiles/ 
#     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/mapfiles/)

add_library(UCM_Project ${UCM_SOURCES} ${UCM_HEADERS})