cmake_minimum_required(VERSION 3.16)
project(CalbaCraft)

# ---- Checks ----
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
        "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
set(CONAN_SYSTEM_INCLUDES "On")
conan_basic_setup()

# ---- Includes and subdirectories ----

include(cmake/project_flags.cmake)

add_subdirectory(src)
