project(SNAKE)
cmake_minimum_required(VERSION 3.0)
include_directories(include)
add_executable(snake main.cpp src/food.cpp src/global.cpp src/map.cpp src/player.cpp src/snake.cpp)