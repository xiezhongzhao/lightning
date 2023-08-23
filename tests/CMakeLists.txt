aux_source_directory(../tests/test_data DIR_TEST_DATA)
aux_source_directory(../tests/test_layer DIR_TEST_LAYER)
aux_source_directory(../tests/test_net DIR_TEST_NET)
aux_source_directory(../tests/test_runtime DIR_TEST_RUNTIME)

message(STATUS "${DIR_TEST_DATA}")
message(STATUS "${DIR_TEST_LAYER}")
message(STATUS "${DIR_TEST_NET}")
message(STATUS "${DIR_TEST_RUNTIME}")

add_executable(test test_main.cpp
        ${DIR_TEST_DATA} ${DIR_TEST_LAYER} ${DIR_TEST_NET} ${DIR_TEST_RUNTIME})
target_link_libraries(test PUBLIC lightning ${lightning_LINKER_LIBS} -lgfortran)
message(STATUS "dep_libs: ${lightning_LINKER_LIBS}")




