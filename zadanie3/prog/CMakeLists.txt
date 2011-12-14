project(ANALIZA_NUMERYCZNA)
cmake_minimum_required(VERSION 2.8)


# find and include boost library
find_package(Boost COMPONENTS python REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(PythonInterp REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${Boost_INCLUDE_DIR})
include_directories(.)


# compile python bindings
add_library(pymatrix SHARED 
  matrix_utils.cpp 
  matrix_arithmetic.cpp
  matrix_norm.cpp
  matrix_upper_triangular.cpp
  python_bindings.cpp)
set_target_properties(pymatrix PROPERTIES PREFIX "")
target_link_libraries(pymatrix 
  ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})


add_custom_command(TARGET pymatrix POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/pymatrix.so ${CMAKE_SOURCE_DIR}/unittests/)

# compile test c++ program
add_executable(prog program.cpp)
target_link_libraries(prog pymatrix)


# add tests
enable_testing()
add_test(library_test ${PYTHON_EXECUTABLE} 
        ${CMAKE_SOURCE_DIR}/unittests/library_test.py)

add_test(norms_test ${PYTHON_EXECUTABLE} 
        ${CMAKE_SOURCE_DIR}/unittests/norms_test.py)

add_test(arithmetic_test ${PYTHON_EXECUTABLE} 
        ${CMAKE_SOURCE_DIR}/unittests/arithmetic_test.py)
