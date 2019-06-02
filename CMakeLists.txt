cmake_minimum_required(VERSION 2.8)

project( Unsu )
set (Unsu_VERSION_MAJOR 2)
set (Unsu_VERSION_MINOR 0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "cmake")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_OPT_ARCH_NATIVE_SUPPORTED)
if (COMPILER_OPT_ARCH_NATIVE_SUPPORTED)
	message(STATUS "Native Arch Supported")
endif()

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

SET(CMAKE_CXX_FLAGS_GPROF "-pg")
if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to Release")
	set(CMAKE_BUILD_TYPE "Release")
endif()

if(APPLE)
	set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
endif(APPLE)

subdirs(src)

