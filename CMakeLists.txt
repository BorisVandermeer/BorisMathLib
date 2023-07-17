cmake_minimum_required(VERSION 3.0.2)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    SET(IS_TOP_DIR YES)
    SET(ENABLE_TEST YES)
    project(BorisMathLib)
else()
    SET(IS_TOP_DIR NO)
    SET(ENABLE_TEST NO)
endif()

SET(THIS_VERSION 0.0.1)

include_directories(.)

aux_source_directory(Points RefPoints_SRC_FILES)
aux_source_directory(Curves Curves_SRC_FILES)
aux_source_directory(Interplot Interpolot_SRC_FILES)

add_library(BORIS_MATH_LIB ${RefPoints_SRC_FILES} ${Curves_SRC_FILES} ${Interpolot_SRC_FILES})

if(IS_TOP_DIR)
    SET(BORIS_MATH_LIBRARIES BORIS_MATH_LIB)
    SET(BORIS_MATH_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
else()
    SET(BORIS_MATH_VERSION THIS_VERSION PARENT_SCOPE)
    SET(BORIS_MATH_FOUND YES PARENT_SCOPE)
    SET(BORIS_MATH_LIBRARIES BORIS_MATH_LIB PARENT_SCOPE)
    SET(BORIS_MATH_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
endif()

if(ENABLE_TEST) 
    add_subdirectory(test)
endif()