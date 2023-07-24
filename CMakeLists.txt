cmake_minimum_required(VERSION 3.16.3)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAEK_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_MODULE_PATH}")

project(lightning)

### for benchmark, OpenMP, Armadillo, glog, BLAS, LAPACK
include(${PROJECT_SOURCE_DIR}/cmake/ThirdParty.cmake)

set(BUILD_DEMO OFF)
if(BUILD_DEMO)
    message(STATUS "BUILD DEMO PROJECT")
    add_subdirectory(demos)
endif()

set(BUILD_TOOL OFF)
if(BUILD_TOOL)
    message(STATUS "BUILD TOOL PROJECT")
    add_subdirectory(tools)
endif()

set(BUILD_BENCHMARK OFF)
if(BUILD_BENCHMARK)
    message(STATUS "BUILD BENCHMARK PROJECT")
    add_subdirectory(benchmark)
endif()

add_subdirectory(lightning)
add_subdirectory(tests)


