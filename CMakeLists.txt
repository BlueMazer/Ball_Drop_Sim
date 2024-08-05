cmake_minimum_required(VERSION 3.27)
project(Ball_Drop_Phys)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ball_Drop_Phys main.cpp
        Ball.h
        ball_simulation.cpp
        common.h)
