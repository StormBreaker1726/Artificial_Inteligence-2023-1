cmake_minimum_required(VERSION 3.10)

project(N-Puzzle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native -funroll-loops")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -O3 -march=native -mtune=native -funroll-loops")

file(GLOB source_files
            "*.h"
            "*.hpp"
            "*.cpp"
            "source/*.cpp"
            "source/*.c"
            "include/*.h"
            "include/*.hpp"
    )
add_executable(npzz ${source_files})

include_directories(./include)