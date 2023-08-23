cmake_minimum_required (VERSION 3.0)
project (ARBlockT1)
set(CMAKE_CXX_FLAGS "-std=c++11")
find_package(OpenCV 4.2 REQUIRED)

LINK_LIBRARIES(${OpenCV_LIBS})

add_executable(homog homog.cpp rva.cpp)




