add_executable(test_input src/unit_input.cpp)
target_link_libraries(test_input IOLib GTest::Main)
add_test(NAME test_input COMMAND test_input)