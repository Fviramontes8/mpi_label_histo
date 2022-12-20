import numpy as np
import matplotlib.pyplot as plt

def plot_bar_graph(data: list, labels: np.array, title: str) -> None:
	plt.bar(labels, data)
	plt.title(title)
	plt.ylabel("Time (seconds)")
	plt.xlabel("Implementation approach")
	plt.show()

def main() -> None:
	x_labels = [ "Serial", "MPI" ]
	two_proc_serial_duration = np.mean([ 1.21413, 1.21618 ])

	two_proc_mpi_duration = np.mean([ 0.647551, 0.647569 ])

	runtime_durations = [ two_proc_serial_duration, two_proc_mpi_duration ]
	print(runtime_durations)
	print(f"Two proc speedup: {runtime_durations[0]/runtime_durations[1]}")
	plot_bar_graph(runtime_durations, x_labels, "Serial v. two processes")

	four_proc_serial_duration= np.mean(
		[
			1.34181,
			1.34182,
			1.3418,
			1.34182
		]
	)
	four_proc_mpi_duration = np.mean(
		[
			0.329313,
			0.329335,
			0.330115,
			0.330112
		]
	)
	runtime_durations = [four_proc_serial_duration, four_proc_mpi_duration ]
	print(runtime_durations)
	print(f"Four proc speedup: {runtime_durations[0]/runtime_durations[1]}")
	plot_bar_graph(runtime_durations, x_labels, "Serial v. four processes")

	six_proc_serial_duration = np.mean(
		[
			1.27243,
			1.27108,
			1.27119,
			1.27245,
			1.27126,
			1.27109

		]
	)

	six_proc_mpi_duration = np.mean(
		[
			0.216102,
			0.216559,
			0.219381,
			0.227793,
			0.229399,
			0.228034,
		]
	)

	runtime_durations = [six_proc_serial_duration, six_proc_mpi_duration ]
	print(runtime_durations)
	print(f"Six proc speedup: {runtime_durations[0]/runtime_durations[1]}")
	plot_bar_graph(runtime_durations, x_labels, "Serial v. six processes")

	mpi_durations = [
		two_proc_mpi_duration,
		four_proc_mpi_duration,
		six_proc_mpi_duration
	]

	serial_durations = [
		two_proc_serial_duration,
		four_proc_serial_duration,
		six_proc_serial_duration
	]

	plt.title("Serial histogram runtime")
	plt.ylabel("Time (seconds)")
	plt.xlabel("Number of processes")
	x_axis = [2, 4, 6]
	plt.plot(x_axis, serial_durations, "k-o")
	plt.show()

	plt.title("MPI histogram runtime")
	plt.ylabel("Time (seconds)")
	plt.xlabel("Number of processes")
	x_axis = [2, 4, 6]
	plt.plot(x_axis, mpi_durations, "k-o")
	plt.show()

if __name__ == "__main__":
	main()
