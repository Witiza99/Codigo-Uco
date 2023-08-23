CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(minitutorial_opencv)
ENABLE_LANGUAGE(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -Wall")

FIND_PACKAGE(OpenCV REQUIRED )
find_package(PCL 1.3 REQUIRED COMPONENTS common io)
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories (${OpenCV_INCLUDE_DIRS})
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(practica6 practica6.cc)
target_link_libraries(practica6 ${PCL_LIBRARIES})
target_link_libraries(practica6 ${OpenCV_LIBS})







 
