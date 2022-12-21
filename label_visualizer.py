import matplotlib.pyplot as plt
import numpy as np

def main() -> None:
    with open("histo_data.txt") as infile:
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
    main()
