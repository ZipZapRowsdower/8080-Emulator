include_directories(include)

add_executable(emulator src/emulator.cpp
        src/instructions.cpp
        src/libretro.cpp
        src/processor.cpp
        src/states.cpp)
add_custom_target(run ${PROJECT_SOURCE_DIR}/build/emulator ${PROJECT_SOURCE_DIR}/data/test)

add_library(retro8080 SHARED
        src/emulator.cpp
        src/instructions.cpp
        src/libretro.cpp
        src/processor.cpp
        src/states.cpp)
set_target_properties(retro8080 PROPERTIES PUBLIC_HEADER include/libretro.h)

install(TARGETS emulator
        DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS retro8080
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_subdirectory(tests)