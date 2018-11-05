cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

project(BigNumber)

file(GLOB SOURCES
    include/*.cpp
    include/*.h
    tests/*.cpp
    tests/*.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
