cmake_minimum_required(VERSION 3.16.3)
project(lightning)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_DEMO OFF)
if(BUILD_DEMO)
    message(STATUS "BUILD DEMO PROJECT")
    add_subdirectory(demos)
endif()

find_package(benchmark REQUIRED)
find_package(OpenMP REQUIRED)
find_package(Armadillo REQUIRED)
find_package(BLAS REQUIRED)
find_package(glog REQUIRED)
#find_package(LAPACK REQUIRED)

set(link_lib glog::glog)
set(link_lib ${link_lib} pthread)
set(link_math_lib ${ARMADILLO_LIBRARIES} ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

add_executable(lightning main.cpp)

target_link_libraries(lightning  ${link_lib} ${link_math_lib} OpenMP::OpenMP_CXX)

target_include_directories(lightning PUBLIC ${benchmark_INCLUDE_DIRS})
target_include_directories(lightning PUBLIC ${glog_INCLUDE_DIR})
target_include_directories(lightning PUBLIC ${GTest_INCLUDE_DIR})
target_include_directories(lightning PUBLIC ${Armadillo_INCLUDE_DIR})










