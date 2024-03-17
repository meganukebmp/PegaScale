cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME Zmey)

project(${PROJECT_NAME})

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")

option(BUILD_EXAMPLES OFF)
option(BUILD_CTL OFF)
option(BUILD_ORM OFF)
option(BUILD_BROTLI OFF)
add_subdirectory(lib/drogon)
target_link_libraries(${PROJECT_NAME} PRIVATE drogon)

add_subdirectory(assets)
add_subdirectory(microdns)
add_dependencies(${PROJECT_NAME} microdns GenAssets)