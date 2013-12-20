#
# Project configuration
#

cmake_minimum_required(VERSION 2.6)
project(pChase)

set (pChase_VERSION_MAJOR 0)
set (pChase_VERSION_MINOR 4)

find_package(Threads)

find_library(LIBNUMA numa)
option(USE_LIBNUMA "Build against NUMA libraries" ON) 

include_directories(lib)
add_subdirectory(lib/AsmJit)


#
# Code compilation
#

add_library(experiment src/experiment.h src/experiment.cpp)

add_library(thread src/thread.h src/thread.cpp)

add_library(lock src/lock.h src/lock.cpp)

add_library(output src/output.h src/output.cpp)

add_library(run src/run.h src/run.cpp)
target_link_libraries(run lock thread)

add_library(spinbarrier src/spinbarrier.h src/spinbarrier.cpp)

add_library(timer src/timer.h src/timer.cpp)

add_executable (chase src/main.cpp)
target_link_libraries(chase run timer output experiment spinbarrier)
target_link_libraries(chase ${CMAKE_THREAD_LIBS_INIT})
if (USE_LIBNUMA)
	if(LIBNUMA)
		target_link_libraries(chase ${LIBNUMA})
	else ()
		message(STATUS "WARNING: libnuma not found, not compiling against it")
	endif ()
endif ()
target_link_libraries(chase AsmJit)
