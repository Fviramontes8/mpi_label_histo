set(HEADER_HISTO_DIR 
	"${mpi_label_histo_SOURCE_DIR}/include/histo_from_dir.hpp"
)
set(HEADER_MPI_HISTO_DIR 
	"${mpi_label_histo_SOURCE_DIR}/include/mpi_histo_from_dir.hpp"
)
set(HEADER_TIMER "${mpi_label_histo_SOURCE_DIR}/include/timer.hpp")

add_library(histo_from_dir_lib histo_from_dir_impl.cpp ${HEADER_HISTO_DIR})
add_library(mpi_histo_from_dir_lib
	mpi_histo_from_dir_impl.cpp
	${HEADER_MPI_HISTO_DIR}
)
add_library(timer_lib timer_impl.cpp ${HEADER_TIMER})

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_HISTO_DIR} ${HEADER_MPI_HISTO_DIR} ${HEADER_TIMER}
)
