cmake_minimum_required(VERSION 3.22)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME}
	app.cpp
	${PROJECT_SOURCE_DIR}/src/mpi_histo_impl.cpp
)

target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
