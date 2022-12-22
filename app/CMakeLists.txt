cmake_minimum_required(VERSION 3.22)

add_executable(${PROJECT_NAME}
	app.cpp
	${PROJECT_SOURCE_DIR}/src/mpi_histo_impl.cpp
)
