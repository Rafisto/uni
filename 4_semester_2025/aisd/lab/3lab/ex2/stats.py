import numpy as np
import subprocess
import os
import matplotlib.pyplot as plt
from multiprocessing import Pool

range_lo = 100
range_hi = 50001
range_step = 1000
lengths = list(range(range_lo, range_hi, range_step))

k_values = [50]
generators = ["../ex1/generator_random", "../ex1/generator_ascending", "../ex1/generator_descending"]
sorters = ["../ex1/random_select", "../ex1/quick_select"]

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
            return (n, sorter, generator, None, None)
    
    print(f"Worker done on {generator}, {sorter}, {n}, {k}")
    return (n, sorter, generator, np.mean(comparisons), np.mean(swaps))

def run_experiments():
    results = {
        k: {
            sorter: {
                generator: {"n": [], "comparisons": [], "swaps": []}
                for generator in generators
            } for sorter in sorters
        } for k in k_values
    }
    
    for k in k_values:
        tasks = [(generator, sorter, n, k) for sorter in sorters for n in lengths for generator in generators]
        
        with Pool() as pool:
            results_list = pool.map(run_test, tasks)
            
        for n, sorter, generator, comparisons, swaps in sorted(results_list, key=lambda x: x[0]):
            if comparisons is not None and swaps is not None:
                print(f"n={n}, sorter={sorter}, generator={generator}, comparisons={comparisons}, swaps={swaps}")
                results[k][sorter][generator]["n"].append(n)
                results[k][sorter][generator]["comparisons"].append(comparisons)
                results[k][sorter][generator]["swaps"].append(swaps)
    return results

def plot_results(results):
    for k, data in results.items():
        for metric, ylabel in [("comparisons", "mean_comparisons"), ("swaps", "mean_swaps")]:
            plt.figure(figsize=(10, 6))
            for sorter, sorter_data in data.items():
                for generator, gen_data in sorter_data.items():
                    sorted_indices = np.argsort(gen_data["n"])
                    sorted_n = np.array(gen_data["n"])[sorted_indices]
                    sorted_metric = np.array(gen_data[metric])[sorted_indices]
                    plt.plot(
                        sorted_n,
                        sorted_metric,
                        label=f"{os.path.basename(sorter)}-{os.path.basename(generator)}",
                        marker="o"
                    )


            plt.title(f"lab3.2 {ylabel} in relation with n (k={k})")
            plt.xlabel("n")
            plt.ylabel(ylabel)
            plt.legend()
            plt.grid()
            plt.savefig(f"{metric}_k{k}.png")
            plt.close()

            plt.figure(figsize=(10, 6))
            for sorter, sorter_data in data.items():
                for generator, gen_data in sorter_data.items():
                    sorted_indices = np.argsort(gen_data["n"])
                    sorted_n = np.array(gen_data["n"])[sorted_indices]
                    sorted_metric = np.array(gen_data[metric])[sorted_indices] / sorted_n
                    plt.plot(
                        sorted_n,
                        sorted_metric,
                        label=f"{os.path.basename(sorter)}-{os.path.basename(generator)}",
                        marker="o"
                    )

            plt.title(f"lab3.2 {ylabel}/n in relation with n (k={k})")
            plt.xlabel("n")
            plt.ylabel(f"{ylabel} / n")
            plt.legend()
            plt.grid()
            plt.savefig(f"{metric}_k{k}_over_n.png")
            plt.close()


if __name__ == "__main__":
    results = run_experiments()
    plot_results(results)