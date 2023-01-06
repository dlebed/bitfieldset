set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

if (NOT DEFINED default_build_type)
	set(default_build_type "Release")
endif()

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

# CPU options and optimization settings
add_compile_options(
	${CPU_OPTIONS}
	$<$<CONFIG:RELEASE>:-O2>
	$<$<CONFIG:DEBUG>:-Og>
	$<$<CONFIG:DEBUG>:-g>
)

# Typical embedded C++ compiler options
add_compile_options(
	$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
	$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
	$<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
	$<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
)

add_compile_options(
	$<$<COMPILE_LANGUAGE:CXX>:-Wold-style-cast>

	-Werror
	-Wall
	-Wextra
	-Wcast-align
	-Wconversion
	-Wno-sign-conversion
	-Wshadow
	-Wno-missing-field-initializers
	-Wno-c99-designator
)

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
	add_compile_options(
		-fstrict-volatile-bitfields
		$<$<COMPILE_LANGUAGE:CXX>:-Wsuggest-override>
		-Wlogical-op
		-Wsuggest-final-types
		-Wsuggest-final-methods
	)
endif()

add_compile_definitions(
		$<$<CONFIG:DEBUG>:DEBUG>
		$<$<CONFIG:DEBUG>:DEBUG_EN=1>
		$<$<CONFIG:RELEASE>:DEBUG_EN=0>
)
