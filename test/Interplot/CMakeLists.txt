cmake_minimum_required(VERSION 3.0.2)

find_package(OpenCV REQUIRED)

include_directories(${BORIS_MATH_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(test_BSpline test_BSpline.cpp)
target_link_libraries(test_BSpline ${OpenCV_LIBS} ${BORIS_MATH_LIBRARIES})