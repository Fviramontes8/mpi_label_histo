cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3")

project(
	mpi_label_histo
	VERSION 1.0
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
