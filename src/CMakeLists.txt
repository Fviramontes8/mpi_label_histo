set(HEADER_MPI_HISTO_DIR 
	"${mpi_label_histo_SOURCE_DIR}/include/mpi_histo.hpp"
)
set(HEADER_PRINT_DIRECTORY
	"${mpi_label_histo_SOURCE_DIR}/include/print_directory.hpp"
)
set(HEADER_PARSE_ARGS
	"${mpi_label_histo_SOURCE_DIR}/include/arg_parser.hpp"
)
set(HEADER_HISTO_IO
	"${mpi_label_histo_SOURCE_DIR}/include/histo_io.hpp"
)

add_library(mpi_histo_from_dir_lib
	mpi_histo_impl.cpp
	${HEADER_MPI_HISTO_DIR}
)

add_library(print_directory_lib
	SHARED
	print_directory_impl.cpp
	${HEADER_PRINT_DIRECTORY}
)

add_library(arg_parser_lib
	arg_parser_impl.cpp
	${HEADER_PRINT_DIRECTORY}
)

add_library(histo_io_lib
	histo_io_impl.cpp
	${HEADER_PRINT_DIRECTORY}
)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_MPI_HISTO_DIR} ${HEADER_PRINT_DIRECTORY} ${HEADER_PARSE_ARGS} ${HEADER_HISTO_IO}
)
