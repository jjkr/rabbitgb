cmake_minimum_required(VERSION 3.0.0)
project(rabbitgb VERSION 0.1.0)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(src)