import argparse
import matplotlib.pyplot as plt
import numpy as np

def parse_opt():
    parser = argparse.ArgumentParser(
        description="Script to plot data from mpi_label_histo"
    )
    parser.add_argument(
        "--file-path",
        type=str,
        action="store",
        required=True,
        help="File to open with histogram data"
    )
    return parser.parse_args()


def main(opt: argparse.Namespace) -> None:
    with open(opt.file_path) as infile:
        file_data = infile.readlines()
        list_data = file_data[0].split(' ')

    list_data = list_data[:30]
    np_data = np.array(list_data, dtype=int)
    classes = [ i for i in range(30) ]

    plt.bar(classes, np_data)
    plt.title("Histogram of classes")
    plt.xlabel("Objects of interest (Classes)")
    plt.ylabel("Number of occurrences in dataset")
    plt.show()

if __name__ == "__main__":
    opt = parse_opt()
    main(opt)
