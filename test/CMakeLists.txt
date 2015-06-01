#add_subdirectory(ast)

#-----------------------------------------------------------------------------------------
# Collect Source Files
#-----------------------------------------------------------------------------------------
file( GLOB SOURCES *.cpp)

#-----------------------------------------------------------------------------------------
# Boost Settings
#-----------------------------------------------------------------------------------------
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package( Boost COMPONENTS REQUIRED )

#-----------------------------------------------------------------------------------------
# Executable Definition
#-----------------------------------------------------------------------------------------
if(Boost_FOUND)
     include_directories(${Boost_INCLUDE_DIRS} $opt/AMDAPP/SDK/include)
		#$opt/AMDAPP/SDK/include
		#$opt/intel/opencl-sdk/include
     add_executable(test_01 ${SOURCES})
     target_link_libraries(test_01 ${Boost_LIBRARIES} /opt/AMDAPP/SDK/lib/libOpenCL.so)
		#/opt/AMDAPP/SDK/lib/libOpenCL.so
		#/opt/intel/opencl-sdk/lib64/?.so
endif()
