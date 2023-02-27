# Start of building/compiling image
FROM ubuntu:20.04 as builder

# Timezone must be configures apriori or else the container build process will
#	  freeze.
ENV TZ=America/Denver
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install build/compile dependencies
RUN apt-get update
RUN apt-get install git g++ cmake libboost-program-options-dev libopenmpi-dev -y

# Clone mpi label histo repository
RUN git clone https://github.com/fviramontes8/mpi_label_histo

# Changes working directory to repo, builds project files, and compiles program
WORKDIR /mpi_label_histo
RUN cmake -B build
RUN cmake --build build --config Release
# End of building/compiling image

# Start of runtime image
FROM ubuntu:20.04 as runtime

# Timezone must be configures apriori or else the container build process will
#	  freeze.
ENV TZ=America/Denver
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install runtime dependencies
RUN apt-get update
RUN apt-get install libboost-program-options-dev libopenmpi-dev -y

# Copy executable from building/compiling image
COPY --from=builder /mpi_label_histo/build/app/mpi_label_histo .

# (Optional) Run help statement
# RUN mpirun --allow-run-as-root -n 2 ./build/app/mpi_label_histo -h

# Consider adding things like folders to analyze as well as adding command to
#  analyze data

# End of runtime image