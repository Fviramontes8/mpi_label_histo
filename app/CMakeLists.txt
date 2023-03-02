cmake_minimum_required(VERSION 3.14)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME}
	app.cpp
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC ${MPI_LIBRARIES}
	PUBLIC ${Boost_LIBRARIES}
	PUBLIC mpi_histo_from_dir_lib
	PUBLIC print_directory_lib
	PUBLIC arg_parser_lib
	PUBLIC histo_io_lib
)
