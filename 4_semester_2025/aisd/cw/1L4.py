import numpy as np
from random import randint, sample
from multiprocessing import Pool, cpu_count

import matplotlib.pyplot as plt

def partition(arr, low, high, pivot_index):
    """Partition the array around the pivot value."""
    pivot = arr[pivot_index]
    arr[pivot_index], arr[high] = arr[high], arr[pivot_index]  # Move pivot to end
    i = low
    for j in range(low, high):
        if arr[j] <= pivot:
            arr[i], arr[j] = arr[j], arr[i]
            i += 1
    arr[i], arr[high] = arr[high], arr[i]  # Move pivot to its final place
    return i

def simulate_trial(args):
    """Simulate a single trial and return the distribution of the partition sizes"""
    n, alpha, pivot_strategy = args
    arr = np.random.randint(0, 1000, n)
    low, high = 0, len(arr) - 1
    
    if pivot_strategy == "random":
        pivot_index = randint(low, high)
    elif pivot_strategy == "median_of_three":
        pivot_candidates = sample(range(low, high + 1), 3)
        pivot_index = sorted(pivot_candidates, key=lambda x: arr[x])[1]
    else:
        raise ValueError("Invalid pivot strategy")
    
    partition_index = partition(arr, low, high, pivot_index)
    left_size = partition_index - low
    right_size = high - partition_index
    total_size = left_size + right_size + 1
    left_ratio = left_size / total_size
    
    # return 1 if left_ratio <= alpha else 0
    return 1 if (left_ratio == alpha or left_ratio == 1 - alpha) else 0

def simulate_partition_probabilities(n, alpha_values, pivot_strategy, trials=10000):
    """Simulate partition probabilities using multiprocessing."""
    probabilities = {alpha: 0 for alpha in alpha_values}
    
    for i in range(trials):
        print(f"Trial {i}")
        arr = np.random.randint(0, 1000, n)
        low, high = 0, len(arr) - 1    
       
        if pivot_strategy == "random":
            pivot_index = randint(low, high)
        elif pivot_strategy == "median_of_three":
            pivot_candidates = sample(range(low, high + 1), 3)
            pivot_index = sorted(pivot_candidates, key=lambda x: arr[x])[1]
        else:
            raise ValueError("Invalid pivot strategy")
    
        partition_index = partition(arr, low, high, pivot_index)
        left_size = partition_index - low
        right_size = high - partition_index
        total_size = left_size + right_size + 1
        left_ratio = left_size / total_size

        ratio = min(left_ratio, 1 - left_ratio)
        for alpha in alpha_values:
            if alpha - 0.01 <= ratio < alpha + 0.01:
                probabilities[alpha] += 1
        
    # Normalize probabilities
    for alpha in alpha_values:
        probabilities[alpha] /= trials

    return [probabilities[alpha] for alpha in alpha_values]


def main():
    n = 1000
    alpha_values = np.arange(0.01, 0.51, 0.01)
    
    print("Simulating partition probabilities for random pivot...")
    random_pivot_probs = simulate_partition_probabilities(n, alpha_values, "random")
    
    print("Simulating partition probabilities for median of three pivot...")
    median_of_three_probs = simulate_partition_probabilities(n, alpha_values, "median_of_three")
    
    plt.figure(figsize=(10, 6))
    plt.plot(alpha_values, random_pivot_probs, label="Random Pivot", marker='o')
    plt.plot(alpha_values, median_of_three_probs, label="Median of Three Pivot", marker='x')

    plt.plot(alpha_values, [0.04 for i in alpha_values], label="alpha Function", linestyle='--', color='gray')
    plt.plot(alpha_values, 1/10*np.sqrt(alpha_values)-0.01, label="sqrt alpha Function", linestyle='--', color='red')
    plt.plot(alpha_values, 1/10*np.log2(alpha_values+1), label="log2 alpha Function", linestyle='--', color='orange')

    plt.xlabel("Alpha ($\\alpha$)")
    plt.ylabel("Probability")


    plt.title("Partition Probability vs Alpha")
    plt.legend()
    plt.grid()
    plt.savefig("1L4.png")


if __name__ == "__main__":
    main()