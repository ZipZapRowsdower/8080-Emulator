cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(8080_Emulator VERSION 0.1 LANGUAGES CXX)

include_directories("${PROJECT_SOURCE_DIR}/src/include")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(emulator ${SOURCES})
add_custom_target(run ${PROJECT_SOURCE_DIR}/build/emulator ${PROJECT_SOURCE_DIR}/data/test)

install(TARGETS emulator DESTINATION ${PROJECT_SOURCE_DIR}/bin)

enable_testing()
add_subdirectory(test)
