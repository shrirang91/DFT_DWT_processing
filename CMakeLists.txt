project(Phase3)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-std=c++11)

find_package(OpenCV REQUIRED)


add_executable(task1 task1.cpp task1-blockprocessor.cpp task1-histogramprocessor.cpp task1-dctprocessor.cpp task1-dwtprocessor.cpp)
target_link_libraries(task1 ${OpenCV_LIBS})

add_executable(task2 task2.cpp)
target_link_libraries(task2 ${OpenCV_LIBS})

add_executable(task3 task3.cpp)
target_link_libraries(task3 ${OpenCV_LIBS})