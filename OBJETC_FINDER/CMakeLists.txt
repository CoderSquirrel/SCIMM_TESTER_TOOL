cmake_minimum_required(VERSION 3.3)
project(OBJECT_FINDER)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES testedivisao.cpp)

add_executable(OBJECT_FINDER ${SOURCE_FILES})

FIND_PACKAGE( OpenCV REQUIRED)
set(OpenCV_FOUND 1)
target_link_libraries(OBJECT_FINDER ${OpenCV_LIBS} )