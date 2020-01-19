find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(emulator_test emulator_test.cpp)
target_link_libraries(emulator_test ${GTEST_LIBRARIES} pthread)
add_test(NAME emulator_test
         COMMAND emulator_test)

add_executable(processor_test processor_test.cpp ${PROJECT_SOURCE_DIR}/src/processor.cpp)
target_link_libraries(processor_test ${GTEST_LIBRARIES} pthread)
add_test(NAME processor_test
         COMMAND processor_test)

add_executable(states_test states_test.cpp ${PROJECT_SOURCE_DIR}/src/states.cpp ${PROJECT_SOURCE_DIR}/src/processor.cpp)
target_link_libraries(states_test ${GTEST_LIBRARIES} pthread)
add_test(NAME states_test
         COMMAND states_test ${PROJECT_SOURCE_DIR}/test/test_file)
