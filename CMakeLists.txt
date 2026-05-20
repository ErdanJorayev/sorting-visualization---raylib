cmake_minimum_required(VERSION 3.20)
project(MySort C)

set(CMAKE_C_STANDARD 23)

find_package(raylib REQUIRED)

add_executable(MySort 
    main.c 
    viz_func.c 
    sort_func.c
)

target_link_libraries(MySort PRIVATE raylib)
