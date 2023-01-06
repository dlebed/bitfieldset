# To add test target use
#	tests_add_test(my_test_target test1.cpp test2.cpp)
macro(tests_add_test test_name)
	set(TestFiles ${ARGN})

	add_executable(${test_name} ${TestFiles})

	add_test(NAME ${test_name} COMMAND ${test_name})

	target_link_libraries(${test_name} gmock_main)

	list(APPEND TEST_TARGETS ${test_name})

	get_directory_property(hasParent PARENT_DIRECTORY)

	if(hasParent)
		set(TEST_TARGETS ${TEST_TARGETS} PARENT_SCOPE)
	else()
		set(TEST_TARGETS ${TEST_TARGETS})
	endif()
endmacro()

# enable sanitizers
add_compile_options(
	-fsanitize=leak
	-fsanitize=undefined
	-fsanitize=address
)

link_libraries(asan ubsan)
