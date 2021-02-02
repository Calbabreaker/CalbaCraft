cmake_minimum_required(VERSION 1.16)
project(CalbaCraft)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

add_subdirectory("src")