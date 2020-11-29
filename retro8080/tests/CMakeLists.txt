include(GoogleTest)

add_executable(emulator_test emulator_test.cpp)
target_link_libraries(emulator_test pthread gtest)
gtest_discover_tests(emulator_test)

add_executable(processor_test processor_test.cpp ../src/processor.cpp)
target_link_libraries(processor_test pthread gtest)
gtest_discover_tests(processor_test)

add_executable(states_test states_test.cpp ../src/states.cpp ../src/processor.cpp)
target_link_libraries(states_test pthread gtest)
gtest_discover_tests(states_test)
