cmake_minimum_required(VERSION 3.14)

if ((CMAKE_CXX_COMPILER_VERSION VERSION_LESS "11.3.0") AND (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "9.4.0"))
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
else()
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3")

project(
	mpi_label_histo
	VERSION 1.1
	DESCRIPTION "Creates a histogram from YOLO-compatible labels"
	LANGUAGES CXX
)

find_package(MPI)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIR})

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(app)
add_subdirectory(src)
