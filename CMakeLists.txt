cmake_minimum_required (VERSION 3.2)

project (CLPP)

#-----------------------------------------------------------------------------------------
# Compiler Flags
#-----------------------------------------------------------------------------------------
set (CMAKE_CXX_FLAGS "-g -ferror-limit=5 -Wall -Wextra -pedantic -std=c++14 -fdiagnostics-color=auto")

option(USE_CLANG "build application with clang" OFF) # OFF is the default
if (USE_CLANG)
    SET (CMAKE_C_COMPILER             "/usr/bin/clang")
    SET (CMAKE_C_FLAGS                "-Wall -Wextra -pedantic -std=c99 -fdiagnostics-color=auto")
    SET (CMAKE_C_FLAGS_DEBUG          "-g")
    SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
    SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

    SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
    SET (CMAKE_CXX_FLAGS                "-g -ferror-limit=5 -Wall -Wextra -pedantic -std=c++14 -fdiagnostics-color=auto")
    SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
    SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

    SET (CMAKE_AR      "/usr/bin/llvm-ar")
    SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
    SET (CMAKE_NM      "/usr/bin/llvm-nm")
    SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
    SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")
endif (USE_CLANG)

#-----------------------------------------------------------------------------------------
# Version
#-----------------------------------------------------------------------------------------
set (Version_Major 1)
set (Version_Minor 0)
set (Version_Patch 0)
set (Version "${Version_Major}.${Version_Minor}.${Version_Patch}")

#-----------------------------------------------------------------------------------------
# Environment
#-----------------------------------------------------------------------------------------

include_directories (
	${PROJECT_SOURCE_DIR}/include
)

add_subdirectory (test)
