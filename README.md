# MPI LABEL HISTO

![](https://github.com/fviramontes8/mpi_label_histo/actions/workflows/cmake.yml/badge.svg)

## Description
Opens a folder containing many text (txt) files, uses a regular expression to extract information of interest (like the first number of each row). It uses that information to create a histogram. When all files have been analyzed, process 0 then writes the aggregated results into a text file.

Include is a python script to plot the result via `matplotlib`

## Dependencies
This program relies on the following:
```
g++, CMake, Boost's program options, MPI
```

They can be installed with `apt` (tested on Ubuntu 20.04, 22.04, Pop!_OS 20.04, 22.04)

```sh
sudo apt install g++ cmake libboost-program-options-dev libopenmpi-dev -y
```

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
mpirun -n 4 ./build/app/mpi_label_histo -h
```
Brings up program's help message which shows available program options, this is what the output should look like:

```
Permitted options:
  -h [ --help ]         Show the help message
  -p [ --path ] arg     Required path to directory to calculate histogram, it
                        should be relative to the executable path
  -s [ --size ] arg     Size of histogram, typically the number of classes in
                        dataset
  -o [ --outfile ] arg  Filename (.txt) where resulting histogram will be
                        stored
```

It should be noted that the flags `-p` and `-s` are required.

## Run examples
```sh
mpirun -n 4 ./build/app/mpi_label_histo -p ../Datasets/COCO/train/ -s 80
```

The example will grab YOLO-compatible text files and parse all text files in the relative path of `../Datasets/COCO/train` and write histogram data to a text file by the name of `histo_data.txt`

The `-p` flag specifies a path to the folder which contains all the text files (must be a relative path), and the `-s` specifies the number of classes that belong to the labels

## What is YOLO-compatible?
Labels that are YOLO-compatible contain 5 columns:

```
class_number x_centroid y_centroid width height
```

[Here is an example of what that looks like](https://github.com/ultralytics/yolov5/wiki/Train-Custom-Data#11-create-datasetyaml)

![Example image with label visualized](https://user-images.githubusercontent.com/26833433/91506361-c7965000-e886-11ea-8291-c72b98c25eec.jpg)

![Corresponding label file](https://user-images.githubusercontent.com/26833433/112467037-d2568c00-8d66-11eb-8796-55402ac0d62f.png)

## Visualizing Histograms
After running the mpi_label_histo, histogram data is written to a text file. To generate the histogram image, run the following (replace `/path/to/text/file` with the relative path to where you stored the text file generated above).

```sh
python3 label_visualizer.py --file-path /path/to/text/file
```
Running the following should bring up the program's help message that shows the available options.

```sh
python3 label_visualizer.py -h
```
The output should look like:

```
usage: label_visualizer.py [-h] --file-path FILE_PATH [--title TITLE] [--x-label X_LABEL] [--y-label Y_LABEL]

Script to plot data from mpi_label_histo

options:
  -h, --help            show this help message and exit
  --file-path FILE_PATH
                        File to open with histogram data
  --title TITLE         Title for histogram
  --x-label X_LABEL     x-axis label of histogram
  --y-label Y_LABEL     y-axis label of histogram
```

Note that the `--file-path` is required.
