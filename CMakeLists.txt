cmake_minimum_required(VERSION 3.14)
project(SA_IMG4Linux_CLI)

set(CMAKE_CXX_STANDARD 14)

add_executable(SA_IMG4Linux_CLI main.cpp IMGFile.cpp IMGFile.h)