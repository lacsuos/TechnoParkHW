add_executable(test_parallel src/unit.cpp)
target_link_libraries(test_parallel SumDynamic GTest::Main)
add_test(NAME test_parallel COMMAND test_parallel)

add_executable(test_static src/unit.cpp)
target_link_libraries(test_static SumStatic GTest::Main)
add_test(NAME test_static COMMAND test_static)