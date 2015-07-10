#-----------------------------------------------------------------------------------------
# Collect Source Files
#-----------------------------------------------------------------------------------------
file (GLOB SOURCES *.cpp)


add_executable (test_01 ${SOURCES})

#-----------------------------------------------------------------------------------------
# Boost Settings
#-----------------------------------------------------------------------------------------
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package (Boost COMPONENTS REQUIRED)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(test_01 ${Boost_LIBRARIES})
endif()

#-----------------------------------------------------------------------------------------
# OpenCL Settings
#-----------------------------------------------------------------------------------------

find_package (OpenCL REQUIRED)

#OpenCL_FOUND          - True if OpenCL was found
#OpenCL_INCLUDE_DIRS   - include directories for OpenCL
#OpenCL_LIBRARIES      - link against this library to use OpenCL
#OpenCL_VERSION_STRING - Highest supported OpenCL version (e.g. 1.2)
#OpenCL_VERSION_MAJOR  - The major version of the OpenCL implementation
#OpenCL_VERSION_MINOR  - The minor version of the OpenCL implementation

if (OpenCL_FOUND)
	include_directories(${OpenCL_INCLUDE_DIRS})
	target_link_libraries(test_01 ${OpenCL_LIBRARIES})
endif()
