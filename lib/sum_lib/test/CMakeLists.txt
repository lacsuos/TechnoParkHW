add_executable(test_parallel src/unit.cpp)
target_link_libraries(test_parallel SumDynamic GTest::Main)
add_test(NAME test_parallel COMMAND test_parallel)

add_executable(test_static src/unit.cpp)
target_link_libraries(test_static SumStatic GTest::Main)
add_test(NAME test_static COMMAND test_static)

add_executable(stress_static src/stress.c)
target_link_libraries(stress_static SumStatic)
add_test(NAME stress_static COMMAND stress_static)

add_executable(stress_dyn src/stress.c)
target_link_libraries(stress_dyn SumDynamic)
add_test(NAME stress_dyn COMMAND stress_dyn)