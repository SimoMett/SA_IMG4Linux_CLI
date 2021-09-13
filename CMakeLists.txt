cmake_minimum_required(VERSION 3.14)
project(SA_IMG4Linux_CLI)

set(CMAKE_CXX_STANDARD 17)

add_executable(saimgtool src/main.cpp src/IMGFile.cpp src/IMGFile.h)