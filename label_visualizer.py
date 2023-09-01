import argparse
import matplotlib.pyplot as plt
import numpy as np

def parse_opt() -> argparse.Namespace:
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
    parser.add_argument(
        "--title",
        type=str,
        action="store",
        required=False,
        help="Title for histogram"
    )
    parser.add_argument(
        "--x-label",
        type=str,
        action="store",
        required=False,
        help="x-axis label of histogram"
    )
    parser.add_argument(
        "--y-label",
        type=str,
        action="store",
        required=False,
        help="y-axis label of histogram"
    )
    return parser.parse_args()


def main(opt: argparse.Namespace) -> None:
    with open(opt.file_path) as infile:
        file_data = infile.readlines()
        list_data = file_data[0].split(' ')[:-1]

    title_string=opt.title if opt.title else "Histogram of classes"
    xlabel_string=opt.x_label if opt.x_label else "Objects of interest (Classes)"
    ylabel_string=opt.y_label if opt.y_label else "Number of occurrences in dataset"

    np_data = np.array(list_data, dtype=int)
    classes = [ i for i in range(len(np_data)) ]

    plt.bar(classes, np_data)
    plt.title(title_string)
    plt.xlabel(xlabel_string)
    plt.ylabel(ylabel_string)
    plt.show()

if __name__ == "__main__":
    opt = parse_opt()
    main(opt)
