cmake_minimum_required(VERSION 3.23)

project(game)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories( ./includes/ )

add_executable(game src/main.cpp src/agent.cpp src/board.cpp src/ai.cpp)
