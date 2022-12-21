# MPI LABEL HISTO

## Description
Opens a folder containing many text (txt) files, uses a regular expression to extract information of interest (like the first number of each row). It uses that information to create a histogram. When all files have been analyzed, process 0 then writes the aggregated results into a text file.

## Build instructions

```sh
cmake -B build
```

## Compile instructions

```sh
cmake --build build
```

## Run instructions

```sh
mpirun -n 4 ./build/app/mpi_label_histo
```
