project(python_binding_experiments)
cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS python REQUIRED)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${Boost_INCLUDE_DIR})

add_library(test SHARED test.cpp)
set_target_properties(test PROPERTIES PREFIX "")
target_link_libraries(test ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
