cmake_minimum_required(VERSION 3.27.8)
project(Group_Project_v1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")




include_directories(.)

add_executable(Group_Project_v1
        BearGame.cpp
        BearGame.h
        SDL_Plotter.cpp
        Team.h)

target_link_libraries(Group_Project_v1 SDL2main SDL2 SDL2_mixer)