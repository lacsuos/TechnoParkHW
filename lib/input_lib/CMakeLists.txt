add_library(IOLib STATIC src/input.c)
target_include_directories(IOLib PUBLIC include)
add_subdirectory(tests)