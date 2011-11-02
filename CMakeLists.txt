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


#
# Code compilation
#

add_library(Chain src/Chain.h src/Chain.cpp)

add_library(Experiment src/Experiment.h src/Experiment.cpp)

add_library(Thread src/Thread.h src/Thread.cpp)

add_library(Lock src/Lock.h src/Lock.cpp)

add_library(Output src/Output.h src/Output.cpp)

add_library(Run src/Run.h src/Run.cpp)
target_link_libraries(Run Lock Chain Thread)

add_library(SpinBarrier src/SpinBarrier.h src/SpinBarrier.cpp)

add_library(Timer src/Timer.h src/Timer.cpp)

add_library(Types src/Types.h src/Types.cpp)

add_executable (chase src/Main.cpp)
target_link_libraries(chase Run Timer Output Experiment SpinBarrier)
target_link_libraries(chase ${CMAKE_THREAD_LIBS_INIT})
if (USE_LIBNUMA)
	if(LIBNUMA)
		target_link_libraries(pChase ${LIBNUMA})
	else ()
		message(STATUS "WARNING: libnuma not found, not compiling against it")
	endif ()
endif ()
