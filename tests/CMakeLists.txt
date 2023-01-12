cmake_minimum_required(VERSION 3.18)

include(ProcessorCount)

project(cpp-bitfieldset-tests)
enable_testing()

set(default_build_type "Debug")

set(PROJ_DIR ${CMAKE_SOURCE_DIR}/../)

include(${PROJ_DIR}/cmake/settings.cmake)

if(NOT DEFINED GOOGLETEST_DIR)
	set(GOOGLETEST_DIR ${PROJ_DIR}/googletest)
endif()
add_subdirectory(${GOOGLETEST_DIR} googletest)

add_subdirectory(${PROJ_DIR} cpp-bitfieldset)
link_libraries(cpp-bitfieldset)

include(${PROJ_DIR}/cmake/tests.cmake)

# Add tests here
tests_add_test(test_bitfieldset test_bitfieldset.cpp)

ProcessorCount(N_CPU)

add_custom_target(run_tests
	COMMAND ${CMAKE_CTEST_COMMAND} -j ${N_CPU} --output-on-failure
	DEPENDS ${TEST_TARGETS}
)
