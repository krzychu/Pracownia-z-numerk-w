project(ANALIZA_NUMERYCZNA)
cmake_minimum_required(VERSION 2.8)

# find and include boost library
find_package(Boost COMPONENTS python REQUIRED)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${Boost_INCLUDE_DIR})
include_directories(.)


# compile python bindings
add_library(pymatrix SHARED matrix.cpp python_bindings.cpp)
set_target_properties(pymatrix PROPERTIES PREFIX "")
target_link_libraries(pymatrix 
  ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})


# compile test c++ program
add_executable(prog program.cpp)
target_link_libraries(prog pymatrix)
