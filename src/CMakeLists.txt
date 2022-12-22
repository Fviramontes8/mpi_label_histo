set(HEADER_MPI_HISTO_DIR 
	"${mpi_label_histo_SOURCE_DIR}/include/mpi_histo.hpp"
)

add_library(mpi_histo_from_dir_lib
	mpi_histo_impl.cpp
	${HEADER_MPI_HISTO_DIR}
)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_MPI_HISTO_DIR}
)
