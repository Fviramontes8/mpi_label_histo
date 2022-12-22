cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
	mpi_label_histo
	VERSION 1.0
	DESCRIPTION "Creates a histogram from YOLO-compatible labels"
	LANGUAGES CXX
)

find_package(MPI)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(app)
add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES})
