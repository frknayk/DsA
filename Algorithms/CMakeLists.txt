cmake_minimum_required(VERSION 3.24)
project(Implementations)

set(CMAKE_CXX_STANDARD 17)

add_executable(exe_breath_first_search breath_first_search.cpp)
add_executable(exe_depth_first_search depth_first_search.cpp)
add_executable(exe_depth_first_search_v2 depth_first_search_v2.cpp)
