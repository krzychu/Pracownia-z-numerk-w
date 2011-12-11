project(ANALIZA_NUMERYCZNA)
cmake_minimum_required(VERSION 2.8)

# find and include boost library
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
include_directories(.)

# compile matrix manipulation library
add_library(matrix matrix.cpp)
target_link_libraries(matrix ${Boost_LIBRARY_DIR})

# compile test programs
add_executable(does_nothing program.cpp)
target_link_libraries(does_nothing matrix)
