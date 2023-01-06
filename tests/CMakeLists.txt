cmake_minimum_required(VERSION 3.10.2)

include(ProcessorCount)

project(cpp-bitfield-tests)
enable_testing()

set(default_build_type "Debug")

set(PROJ_DIR ${CMAKE_SOURCE_DIR}/../)

include(${PROJ_DIR}/cmake/settings.cmake)

if(NOT DEFINED GOOGLETEST_DIR)
	set(GOOGLETEST_DIR ${PROJ_DIR}/googletest)
endif()
add_subdirectory(${GOOGLETEST_DIR} googletest)

add_subdirectory(${PROJ_DIR} cpp-bitfield)
link_libraries(cpp-bitfield)

include(${PROJ_DIR}/cmake/tests.cmake)

# Add tests here
tests_add_test(test_bitfieldset test_bitfieldset.cpp)

ProcessorCount(N_CPU)

add_custom_target(unit_tests ALL
	COMMAND ${CMAKE_CTEST_COMMAND} -j ${N_CPU} --output-on-failure
	DEPENDS ${TEST_TARGETS}
)
