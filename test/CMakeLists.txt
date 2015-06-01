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
     include_directories(${Boost_INCLUDE_DIRS})
     add_executable(neuronet ${SOURCES})
     target_link_libraries(neuronet ${Boost_LIBRARIES})
endif()
