cmake_minimum_required(VERSION 3.22)

add_executable(${PROJECT_NAME}
	app.cpp
	${PROJECT_SOURCE_DIR}/src/histo_from_dir_impl.cpp
	${PROJECT_SOURCE_DIR}/src/mpi_histo_from_dir_impl.cpp
	${PROJECT_SOURCE_DIR}/src/timer_impl.cpp
)
