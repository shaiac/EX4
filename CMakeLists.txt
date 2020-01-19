cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex4 main.cpp SerialServer.h SerialServer.cpp MyTestClientHandler.h Solver.h CacheManager.h FileCacheManager.h StringReverser.cpp StringReverser.h MyTestClientHandler.cpp server_side.h ClientHandler.h FileCacheManager.cpp State.h Point.cpp Point.h Searcher.h Searchable.h Matrix.cpp Matrix.h DepthFirstSearch.h BestFirstSearch.h BreadthFirstSearch.h Astar.h MyClientHandler.cpp MyClientHandler.h OA.h DSearcher.h MyParallelServer.cpp MyParallelServer.h)