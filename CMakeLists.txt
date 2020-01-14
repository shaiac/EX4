cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex4 main.cpp SerialServer.h SerialServer.cpp MyClientHandler.h Solver.h CacheManager.h FileCacheManager.h StringReverser.cpp StringReverser.h MyClientHandler.cpp server_side.h ClientHandler.h FileCacheManager.cpp)