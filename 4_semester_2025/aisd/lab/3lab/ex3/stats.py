import numpy as np
import subprocess
import os
import matplotlib.pyplot as plt
from multiprocessing import Pool
from multiprocessing import Lock

# Parameters
range_lo = 100
range_hi = 50001
range_step = 1000
lengths = list(range(range_lo, range_hi, range_step))

k_values = [50]
generators = ["../ex1/generator_random"]
sorters = ["../ex3/quick_select 3", "../ex3/quick_select 5", "../ex3/quick_select 7", "../ex3/quick_select 9"]

# Function to run a single test case
def run_test(args):
    generator, sorter, n, k = args
    print(f"Worker run on {generator}, {sorter}, {n}, {k}")
    comparisons = []
    swaps = []
    for _ in range(k):
        try:
            generator_proc = subprocess.Popen(
                [f"{generator}", str(n)], stdout=subprocess.PIPE
            )
            sorter_command = sorter.split()
            sorter_proc = subprocess.Popen(
                sorter_command, stdin=generator_proc.stdout, stdout=subprocess.PIPE
            )
            generator_proc.stdout.close()
            output = sorter_proc.communicate()[0].decode("utf-8")

            for line in output.splitlines():
                if "comparisons" in line:
                    comparisons.append(int(line.split(":")[1].strip()))
                if "swaps" in line:
                    swaps.append(int(line.split(":")[1].strip()))
        except Exception as e:
            print(f"Error running {generator} -> {sorter} for n={n}: {e}")
            return (n, sorter, None, None)
    
    print(f"Worker done on {generator}, {sorter}, {n}, {k}")
    return (n, sorter, np.mean(comparisons), np.mean(swaps))

# Main experiment loop
def run_experiments():
    results = {k: {sorter: {"n": [], "comparisons": [], "swaps": []} for sorter in sorters} for k in k_values}
    
    for k in k_values:
        tasks = [(generator, sorter, n, k) for sorter in sorters for n in lengths for generator in generators]
        
        with Pool() as pool:
            results_list = pool.map(run_test, tasks)
            
        for n, sorter, comparisons, swaps in sorted(results_list, key=lambda x: x[0]):
            if comparisons is not None and swaps is not None:
                print(f"n={n}, sorter={sorter}, comparisons={comparisons}, swaps={swaps}")
                results[k][sorter]["n"].append(n)
                results[k][sorter]["comparisons"].append(comparisons)
                results[k][sorter]["swaps"].append(swaps)
    return results

# Plotting function
def plot_results(results):
    for k, data in results.items():
        for metric, ylabel in [("comparisons", "Average Comparisons"), ("swaps", "Average Swaps")]:
            plt.figure(figsize=(10, 6))
            for sorter, sorter_data in data.items():
                sorted_indices = np.argsort(sorter_data["n"])
                sorted_n = np.array(sorter_data["n"])[sorted_indices]
                sorted_metric = np.array(sorter_data[metric])[sorted_indices]
                plt.plot(
                    sorted_n,
                    sorted_metric,
                    label=f"{sorter}",
                    marker="o"
                )
            plt.title(f"lab3.3 {ylabel} vs n (k={k})")
            plt.xlabel("n")
            plt.ylabel(ylabel)
            plt.legend()
            plt.grid()
            plt.savefig(f"{metric}_k{k}.png")
            plt.close()

            # plot over n
            plt.figure(figsize=(10, 6))
            for sorter, sorter_data in data.items():
                sorted_indices = np.argsort(sorter_data["n"])
                sorted_n = np.array(sorter_data["n"])[sorted_indices]
                sorted_metric = np.array(sorter_data[metric])[sorted_indices] / sorted_n
                plt.plot(
                    sorted_n,
                    sorted_metric,
                    label=sorter,
                    marker="o"
                )
            plt.title(f"lab3.3 {ylabel}/n vs n (k={k})")
            plt.xlabel("n")
            plt.ylabel(ylabel)
            plt.legend()
            plt.grid()
            plt.savefig(f"{metric}_k{k}_over_n.png")
            plt.close()

# Run the experiments and plot results
if __name__ == "__main__":
    results = run_experiments()
    plot_results(results)