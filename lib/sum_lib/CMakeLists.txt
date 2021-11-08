set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

add_library(SumDynamic SHARED src/sum_parallel.c)
target_link_libraries(SumDynamic PUBLIC pthread)
target_include_directories(SumDynamic PUBLIC include)

add_library(SumStatic STATIC src/sum_static.c)
target_include_directories(SumStatic PUBLIC include)

add_subdirectory(test)
