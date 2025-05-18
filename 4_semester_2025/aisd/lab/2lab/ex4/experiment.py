import subprocess
import numpy as np
from multiprocessing import Pool

lengths = list(range(10000, 20001, 10000))
prefix = "small"
k_values = [1, 10, 100]
generators = ["../ex1/generator_random"]
sorters = ["../ex4/dual_pivot_quick_sort"]

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

def run_experiments():
    results = {k: {sorter: {"n": [], "comparisons": [], "swaps": []} for sorter in sorters} for k in k_values}
    
    for k in k_values:
        tasks = [(generator, sorter, n, k) for generator in generators for sorter in sorters for n in lengths]
        with Pool() as pool:
            for n, sorter, avg_comparisons, avg_swaps in pool.map(run_test, tasks):
                if avg_comparisons is not None and avg_swaps is not None:
                    results[k][sorter]["n"].append(n)
                    results[k][sorter]["comparisons"].append(avg_comparisons)
                    results[k][sorter]["swaps"].append(avg_swaps)

    for k in k_values:
        print(f"\nResults for k={k}:")
        for sorter in sorters:
            n_values = np.array(results[k][sorter]["n"])
            comparisons = np.array(results[k][sorter]["comparisons"])
            swaps = np.array(results[k][sorter]["swaps"])
            if len(n_values) > 0:
                comparison_factors = comparisons / (n_values * np.log2(n_values))
                swap_factors = swaps / (n_values * np.log2(n_values))
                avg_comparison_factor = np.mean(comparison_factors)
                avg_swap_factor = np.mean(swap_factors)
                print(f"{sorter}")
                print(f"Average comparison factor = {avg_comparison_factor:.4f}")
                print(f"Average swap factor = {avg_swap_factor:.4f}")

if __name__ == "__main__":
    run_experiments()