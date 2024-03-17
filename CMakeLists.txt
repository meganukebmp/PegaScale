cmake_minimum_required(VERSION 3.10)

project(Zmey)

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(Zmey ${SOURCES})

target_include_directories(Zmey PUBLIC "${PROJECT_SOURCE_DIR}/include")