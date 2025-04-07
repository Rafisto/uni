import numpy as np
import subprocess
import matplotlib.pyplot as plt

# Parameters
n_values = range(1, 20)  # Threshold values from 1 to 100
hybrid_program = "../ex1/hybrid_sort_threshold"
quick_program = "../ex1/quick_sort"

# Function to run a sorting program
def run_sort_program(program, args, input_data):
    try:
        proc = subprocess.Popen(
            [program] + args,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        stdout, stderr = proc.communicate(input=input_data.encode())
        if proc.returncode != 0:
            print(f"Error for program={program}, args={args}: {stderr.decode()}")
            return None, None
        comparisons, swaps = None, None
        for line in stdout.decode().splitlines():
            if "comparisons" in line:
                comparisons = int(line.split(":")[1].strip())
            if "swaps" in line:
                swaps = int(line.split(":")[1].strip())
        return comparisons, swaps
    except Exception as e:
        print(f"Exception for program={program}, args={args}: {e}")
        return None, None

# Generate random input data
def generate_input_data(size=1000):
    return " ".join(map(str, np.random.randint(0, 10000, size)))

# Main function to test thresholds and plot results
def main():
    input_data = generate_input_data()
    hybrid_results = []
    quick_results = []

    # Test hybrid_sort_threshold for different thresholds
    for threshold in n_values:
        comparisons, swaps = run_sort_program(hybrid_program, [str(threshold)], input_data)
        if comparisons is not None and swaps is not None:
            hybrid_results.append((threshold, comparisons, swaps))

    # Test quick_sort
    comparisons, swaps = run_sort_program(quick_program, [], input_data)
    if comparisons is not None and swaps is not None:
        quick_results = [(threshold, comparisons, swaps) for threshold in n_values]

    # Plot the results
    if hybrid_results and quick_results:
        hybrid_thresholds, hybrid_comparisons, hybrid_swaps = zip(*hybrid_results)
        quick_thresholds, quick_comparisons, quick_swaps = zip(*quick_results)

        plt.figure(figsize=(10, 6))
        plt.plot(hybrid_thresholds, hybrid_comparisons, marker="o", label="Hybrid Comparisons")
        plt.plot(hybrid_thresholds, hybrid_swaps, marker="s", label="Hybrid Swaps")
        plt.plot(quick_thresholds, quick_comparisons, marker="^", label="QuickSort Comparisons", linestyle="--")
        plt.plot(quick_thresholds, quick_swaps, marker="v", label="QuickSort Swaps", linestyle="--")
        plt.title("Threshold vs Comparisons and Swaps (Hybrid vs QuickSort)")
        plt.xlabel("Threshold")
        plt.ylabel("Count")
        plt.grid()
        plt.legend()
        plt.savefig("threshold_vs_comparisons_and_swaps_comparison.png")
        plt.show()

if __name__ == "__main__":
    main()