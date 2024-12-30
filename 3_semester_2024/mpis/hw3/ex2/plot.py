import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

# Ensure the output directory exists
os.makedirs("graphs", exist_ok=True)

# Load the data
df = pd.read_csv('insertion_sort_results.csv')

# Group by 'n' and compute averages for each metric
grouped = df.groupby('n').mean()

# Extract columns
n = grouped.index
comparisons = grouped['comparisons']
swaps = grouped['swaps']
cmp_n = grouped['cmp_n']
cmp_n2 = grouped['cmp_n2']
swaps_n = grouped['swaps_n']
swaps_n2 = grouped['swaps_n2']

# Original data for scatter plots
n_full = df['n']
comparisons_full = df['comparisons']
swaps_full = df['swaps']
cmp_n_full = df['cmp_n']
cmp_n2_full = df['cmp_n2']
swaps_n_full = df['swaps_n']
swaps_n2_full = df['swaps_n2']

# Plot settings
plots = [
    ("cmp_vs_n", n_full, comparisons_full, n, comparisons, r"$n$", r"$cmp(n)$"),
    ("s_vs_n", n_full, swaps_full, n, swaps, r"$n$", r"$s(n)$"),
    ("cmp_n_vs_n", n_full, cmp_n_full, n, cmp_n, r"$n$", r"$\frac{cmp(n)}{n}$"),
    ("cmp_n2_vs_n", n_full, cmp_n2_full, n, cmp_n2, r"$n$", r"$\frac{cmp(n)}{n^2}$"),
    ("s_n_vs_n", n_full, swaps_n_full, n, swaps_n, r"$n$", r"$\frac{s(n)}{n}$"),
    ("s_n2_vs_n", n_full, swaps_n2_full, n, swaps_n2, r"$n$", r"$\frac{s(n)}{n^2}$"),
]

# Generate plots
for plot_name, x_full, y_full, x_mean, y_mean, xlabel, ylabel in plots:
    plt.figure(figsize=(6, 6))
    # Scatter plot for individual data points
    plt.scatter(x_full, y_full, label=f"single {ylabel}", color='blue', s=1)
    # Line plot for averages
    plt.plot(x_mean, y_mean, label=f"average {ylabel}", color='red', marker='o', markersize=3)
    plt.title(f"{ylabel} vs {xlabel}")
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"graphs/{plot_name}.png", dpi=300)
    plt.close()
