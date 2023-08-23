cmake_minimum_required (VERSION 3.0)
project (ARBlockT2)
set(CMAKE_CXX_FLAGS "-std=c++11")
find_package(OpenCV REQUIRED)

LINK_LIBRARIES(${OpenCV_LIBS})

add_executable(kps kps.cpp rva.cpp)




