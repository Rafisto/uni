import numpy as np
import subprocess
import os
import matplotlib.pyplot as plt
from multiprocessing import Pool

# Parameters
lengths = list(range(10, 51, 10))
prefix = "small"
k_values = [1, 10, 100]
generators = ["../ex1/generator_random"]
sorters = ["../ex1/insertion_sort", "../ex1/quick_sort", "../ex1/hybrid_sort", "../ex4/dual_pivot_quick_sort", "../ex3/merge_sort", "../ex3/custom_sort"]

# Function to run a single test case
def run_test(args):
    generator, sorter, n, k = args
    comparisons = []
    swaps = []
    for _ in range(k):
        try:
            generator_proc = subprocess.Popen(
                [f"{generator}", str(n)], stdout=subprocess.PIPE
            )
            sorter_proc = subprocess.Popen(
                [f"{sorter}"], stdin=generator_proc.stdout, stdout=subprocess.PIPE
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
                    label=sorter,
                    marker="o"
                )
            plt.title(f"{ylabel} vs n (k={k})")
            plt.xlabel("n")
            plt.ylabel(ylabel)
            plt.legend()
            plt.grid()
            plt.savefig(f"{prefix}_{metric}_k{k}.png")
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
            plt.title(f"{ylabel} over n vs n (k={k})")
            plt.xlabel("n")
            plt.ylabel(ylabel)
            plt.legend()
            plt.grid()
            plt.savefig(f"{prefix}_{metric}_k{k}_over_n.png")
            plt.close()

# Run the experiments and plot results
if __name__ == "__main__":
    results = run_experiments()
    plot_results(results)
    
    prefix = "large"
    lengths = list(range(1000, 50001, 1000))  # n ∈ {1000, 2000, ..., 50000}
    sorters = ["../ex1/quick_sort", "../ex1/hybrid_sort", "../ex4/dual_pivot_quick_sort", "../ex3/merge_sort", "../ex3/custom_sort"]
    results = run_experiments()
    plot_results(results)