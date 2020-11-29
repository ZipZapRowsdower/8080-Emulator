cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(8080_Emulator VERSION 0.1 LANGUAGES CXX)

include_directories("${PROJECT_SOURCE_DIR}/src/include")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(emulator ${PROJECT_SOURCE_DIR}/src/emulator.cpp
	                ${PROJECT_SOURCE_DIR}/src/instructions.cpp
			${PROJECT_SOURCE_DIR}/src/libretro.cpp
			${PROJECT_SOURCE_DIR}/src/processor.cpp
			${PROJECT_SOURCE_DIR}/src/states.cpp)
add_custom_target(run ${PROJECT_SOURCE_DIR}/build/emulator ${PROJECT_SOURCE_DIR}/data/test)

add_library(retro8080 SHARED src/libretro.cpp)
set_target_properties(retro8080 PROPERTIES PUBLIC_HEADER include/libretro.h)

install(TARGETS emulator
	DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS retro8080
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#enable_testing()
#add_subdirectory(test)
