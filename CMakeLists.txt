cmake_minimum_required (VERSION 3.2)

project (CLPP)

#-----------------------------------------------------------------------------------------
# Compiler Flags
#-----------------------------------------------------------------------------------------
set (CMAKE_CXX_FLAGS "-g -Wall -Wextra -pedantic -std=c++14 -fdiagnostics-color=auto")

# -ferror-limit=5

option(USE_CLANG "build application with clang" OFF) # OFF is the default
if (USE_CLANG)
    set (CMAKE_C_COMPILER             "/usr/bin/clang")
    set (CMAKE_C_FLAGS                "-Wall -Wextra -pedantic -std=c99 -fdiagnostics-color=auto")
    set (CMAKE_C_FLAGS_DEBUG          "-g")
    set (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    set (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
    set (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

    set (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
    set (CMAKE_CXX_FLAGS                "-g -ferror-limit=5 -Wall -Wextra -pedantic -std=c++14 -fdiagnostics-color=auto")
    set (CMAKE_CXX_FLAGS_DEBUG          "-g")
    set (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    set (CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
    set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

    set (CMAKE_AR      "/usr/bin/llvm-ar")
    set (CMAKE_LINKER  "/usr/bin/llvm-ld")
    set (CMAKE_NM      "/usr/bin/llvm-nm")
    set (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
    set (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")
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

include_directories (${PROJECT_SOURCE_DIR}/include)

add_subdirectory (${PROJECT_SOURCE_DIR}/test)

