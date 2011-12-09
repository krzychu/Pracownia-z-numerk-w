project(ANALIZA_NUMERYCZNA)
cmake_minimum_required(VERSION 2.8)

add_subdirectory(matlib)
include_directories(matlib)

# compile test programs
add_executable(does_nothing program.cpp)
target_link_libraries(does_nothing MatLib)
