cmake_minimum_required(VERSION 3.14)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME}
	app.cpp
	${PROJECT_SOURCE_DIR}/src/mpi_histo_impl.cpp
	${PROJECT_SOURCE_DIR}/src/arg_parser_impl.cpp
	${PROJECT_SOURCE_DIR}/src/histo_io_impl.cpp
)

target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
