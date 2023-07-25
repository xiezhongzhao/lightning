set(lightning_LINKER_LIBS "")
set(lightning_INCLUDE_DIRS "")

find_package(benchmark REQUIRED)
find_package(OpenMP REQUIRED)
find_package(Armadillo REQUIRED)
find_package(BLAS REQUIRED)
find_package(glog REQUIRED)
find_package(GTest REQUIRED)
#find_package(LAPACK REQUIRED)

#include_directories(${GTEST_INCLUDE_DIRS})

set(link_lib glog::glog benchmark::benchmark OpenMP::OpenMP_CXX pthread)
set(link_lib ${link_lib})
set(link_math_lib ${ARMADILLO_LIBRARIES} ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES} ${GTEST_LIBRARIES})

#list(APPEND lightning_INCLUDE_DIRS ${benchmark_INCLUDE_DIRS}
#        ${glog_INCLUDE_DIR} ${GTest_INCLUDE_DIR} ${Armadillo_INCLUDE_DIR})
list(APPEND lightning_LINKER_LIBS ${link_lib} ${link_math_lib})


