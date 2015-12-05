cmake_minimum_required (VERSION 3.4)
project (TSP_GA)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)
file(GLOB tsp_src "*.h" "*.cpp")
add_executable(TSP_GA ${tsp_src})

