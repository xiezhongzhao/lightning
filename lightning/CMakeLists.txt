file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(lightning SHARED ${srcs})
target_include_directories(lightning PUBLIC include)

