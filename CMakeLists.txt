set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(BUILD_USE_64BITS on)

cmake_minimum_required (VERSION 2.6)
project (Exercise)

# The version number.
set (Exercise_VERSION_MAJOR 1)
set (Exercise_VERSION_MINOR 0)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

include_directories ( 
	${PROJECT_SOURCE_DIR}/include
	$ENV{OSG_INCLUDE_PATH}
	$ENV{OSG_3RDPATRY_ROOT}/include
)
link_directories (
	${PROJECT_SOURCE_DIR}/lib
	$ENV{OSG_LIB_PATH}
	$ENV{OSG_3RDPATRY_ROOT}/lib
)

add_subdirectory (src)