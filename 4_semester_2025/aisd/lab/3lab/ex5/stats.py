import numpy as np
import subprocess
import os
import matplotlib.pyplot as plt
from multiprocessing import Pool
import scipy.optimize

k_values = [10]
generators = ["./generator_descending"]
lengths = list(range(1000, 10001, 1000))
sorters = ["./quick_sort", "./quick_sort_select",
           "./dual_pivot_quick_sort", "./dual_pivot_quick_sort_select"]

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
    results = {k: {sorter: {"n": [], "comparisons": [], "swaps": []}
                   for sorter in sorters} for k in k_values}

    for k in k_values:
        tasks = [(generator, sorter, n, k)
                 for sorter in sorters for n in lengths for generator in generators]

        with Pool() as pool:
            results_list = pool.map(run_test, tasks)

        for n, sorter, comparisons, swaps in sorted(results_list, key=lambda x: x[0]):
            if comparisons is not None and swaps is not None:
                print(
                    f"n={n}, sorter={sorter}, comparisons={comparisons}, swaps={swaps}")
                results[k][sorter]["n"].append(n)
                results[k][sorter]["comparisons"].append(comparisons)
                results[k][sorter]["swaps"].append(swaps)
    return results

# Function to estimate C for a given model


def estimate_constant(x, y, model_fn):
    def model(C):
        return model_fn(x) * C

    def error(C):
        return np.mean((y - model(C))**2)
    result = scipy.optimize.minimize_scalar(
        error, bounds=(1e-6, 1e6), method='bounded')
    return result.x

# Plotting function


def plot_results(results):
    for k, data in results.items():
        for metric, ylabel in [("comparisons", "avg comparisons (worst case)"), ("swaps", "avg swaps (worst case)")]:
            plt.figure(figsize=(10, 6))
            legend_entries = []
            for sorter, sorter_data in data.items():
                sorted_indices = np.argsort(sorter_data["n"])
                x = np.array(sorter_data["n"])[sorted_indices]
                y = np.array(sorter_data[metric])[sorted_indices]
                if len(x) == 0:
                    continue

                label = sorter
                if metric == "comparisons":
                    if "select" in sorter:
                        def model_fn(x): return x * np.log2(x)
                        label_type = "n log n"
                    else:
                        def model_fn(x): return x**2
                        label_type = "n^2"
                    C_est = estimate_constant(x, y, model_fn)
                    label += f" (C ≈ {C_est:.3f}, {label_type})"

                plt.plot(x, y, label=label, marker="o")

            # Reference curves
            xref = np.array(x)
            plt.plot(xref, xref*np.log2(xref), label="n log(n)", linestyle="--")
            plt.plot(xref, xref, label="n", linestyle="--")
            plt.plot(xref, xref**2, label="n^2", linestyle="--")

            plt.yscale("log")
            plt.title(f"lab3.5 {ylabel} vs n (k={k})")
            plt.xlabel("n")
            plt.ylabel(f"{ylabel} (log scale)")
            plt.legend()
            plt.grid()
            plt.tight_layout()
            plt.savefig(f"{metric}_k{k}_log.png")
            plt.close()


# Run the experiments and plot results
if __name__ == "__main__":
    results = run_experiments()
    plot_results(results)
