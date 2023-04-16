cmake_minimum_required(VERSION 3.0)

project(EnvelopeFollower)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES test.cpp EnvelopeFollower.cpp)

find_package(iir REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} iir::iir)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.exe")

target_compile_definitions(${PROJECT_NAME} PRIVATE)