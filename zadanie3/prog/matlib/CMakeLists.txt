# find and include boost library
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
include_directories(.)

# compile matrix manipulation library
add_library(MatLib matrix.cpp)
target_link_libraries(MatLib ${Boost_LIBRARY_DIR})

