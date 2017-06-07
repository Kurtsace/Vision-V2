cmake_minimum_required(VERSION 2.8.3)
project(Vision_V2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lopencv_objdetect -lopencv_highgui -lopencv_imgproc -lopencv_core")

set(SOURCE_FILES main.cpp Vision.cpp Vision.h Sport.h)
add_executable(Vision_V2 ${SOURCE_FILES})

find_package(OpenCV REQUIRED)

target_link_libraries(Vision_V2 ${OpenCV_LIBS})