cmake_minimum_required(VERSION 2.8...3.1)
project( InfoScreen )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
SET(CMAKE_CXX_FLAGS "-O0")
SET(CMAKE_C_FLAGS "-O0")
add_executable( InfoScreen main.cpp ImageObject.cpp)
target_link_libraries( InfoScreen ${OpenCV_LIBS} )