import time
import random
import matplotlib.pyplot as plt
import numpy as np

k = 1000
types = ["start", "middle", "end", "none", "rand"]

def binary_search_recursive(arr, v, left, right, comparisons):
    if left > right:
        return 0, comparisons
    mid = (left + right) // 2
    comparisons += 1
    if arr[mid] == v:
        return 1, comparisons
    elif arr[mid] < v:
        return binary_search_recursive(arr, v, mid + 1, right, comparisons)
    else:
        return binary_search_recursive(arr, v, left, mid - 1, comparisons)

def binary_search(arr, v):
    return binary_search_recursive(arr, v, 0, len(arr) - 1, 0)

def experiment():
    sizes = range(1000, 100001, 1000)
    results_by_type = {t: {"n": [], "comparisons": [], "time": []} for t in types}

    for t in types:
        for n in sizes:
            arr = list(range(n))
            all_comparisons = []
            all_times = []

            print(f"Type: {t}, n = {n}")

            for _ in range(k):
                if t == "start":
                    v = random.choice(arr[:10])
                elif t == "middle":
                    mid_index = n // 2
                    v = random.choice(arr[mid_index - 10: mid_index + 10])
                elif t == "end":
                    v = random.choice(arr[-10:])
                elif t == "rand":
                    v = random.choice(arr)
                else:
                    v = -1 # not present

                start_time = time.time()
                _, comparisons = binary_search(arr, v)
                elapsed_time = time.time() - start_time

                all_comparisons.append(comparisons)
                all_times.append(elapsed_time)

            mean_comparisons = np.mean(all_comparisons)
            mean_time = np.mean(all_times)

            results_by_type[t]["n"].append(n)
            results_by_type[t]["comparisons"].append(mean_comparisons)
            results_by_type[t]["time"].append(mean_time)

    for metric, ylabel in [("comparisons", "lab3.4 Average Comparisons"), ("time", "lab3.4 Average Time (s)")]:
        plt.figure(figsize=(10, 6))
        for t, data in results_by_type.items():
            sorted_indices = np.argsort(data["n"])
            sorted_n = np.array(data["n"])[sorted_indices]
            sorted_metric = np.array(data[metric])[sorted_indices]
            plt.plot(
                sorted_n,
                sorted_metric,
                label=f"{t}",
                marker="o"
            )

        if metric == "comparisons":
            plt.plot(sorted_n, np.log2(sorted_n), label="log2(n)", linestyle="--", color="black")

        plt.title(f"{ylabel} vs n (k={k})")
        plt.xlabel("n")
        plt.ylabel(ylabel)
        plt.legend()
        plt.grid()
        plt.savefig(f"{metric}_k{k}.png")
        plt.close()

if __name__ == "__main__":
    experiment()
