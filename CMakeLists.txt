cmake_minimum_required(VERSION 3.10)
project(8080-Emulator
		VERSION 0.0.1
		DESCRIPTION "Implementation of a basic 8080 emulator as a libretro core"
		LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(googletest)
include_directories(googletest/googletest/include/)
enable_testing()

add_subdirectory(retro8080)