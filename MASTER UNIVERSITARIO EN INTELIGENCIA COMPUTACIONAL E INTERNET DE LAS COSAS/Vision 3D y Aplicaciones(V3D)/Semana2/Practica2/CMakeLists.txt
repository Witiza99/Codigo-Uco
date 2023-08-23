CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(minitutorial_opencv)
ENABLE_LANGUAGE(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -Wall")

FIND_PACKAGE(OpenCV REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")

add_executable(stereo_checkundistorted stereo_checkundistorted.cc)
 
