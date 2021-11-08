cmake_minimum_required(VERSION 3.16)
project(HW2)

add_compile_options(-Wall -Wextra -pedantic)
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

option(ASAN "Enable address sanitizer" ON)
option(USAN "Enable undefined sanitizer" ON)
option(TSAN "Enable thread sanitizer" OFF)

option(COVERAGE "Enable coverage" OFF)
if(COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

if(ASAN OR USAN OR TSAN)
    add_compile_options(-fno-omit-frame-pointer)
    
    if(ASAN)
        add_compile_options(-fsanitize=address)
        add_link_options(-fsanitize=address)
    endif()

    if(USAN)
        add_compile_options(-fsanitize=undefined)
        add_link_options(-fsanitize=undefined)
    endif()

    if(TSAN)
        add_compile_options(-fsanitize=thread)
        add_link_options(-fsanitize=thread)
    endif()

endif()


option(WITH_TESTS "Enable testing" ON)
if(WITH_TESTS)
    find_package(GTest REQUIRED)
    enable_testing()
endif()


add_subdirectory(lib/sum_lib)
add_subdirectory(lib/input_lib)

option(PARALLEL "Connect parallel realisation" OFF)
if(PARALLEL)
    add_executable(task src/main.c)
    target_link_libraries(task IOLib SumDynamic)
else()
    add_executable(task src/main.c)
    target_link_libraries(task IOLib SumStatic)
endif()