import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

# Ensure the graphs directory exists
os.makedirs("graphs", exist_ok=True)

# Read the input data from the main results CSV file
df = pd.read_csv('results.csv')

# Read the intermediate results CSV file (measurements for rep in 0, 49)
intermediate_df = pd.read_csv('results_intermediate.csv')

# Extract columns from the main results DataFrame
n = df['n'].values
b_factor = df['b_factor'].values
u_factor = df['u_factor'].values
c_factor = df['c_factor'].values
d_factor = df['d_factor'].values
r_factor = df['r_factor'].values

# Extract columns from the intermediate results DataFrame
n_intermediate = intermediate_df['n'].values
rep = intermediate_df['rep'].values
b_factor_intermediate = intermediate_df['b_factor'].values
u_factor_intermediate = intermediate_df['u_factor'].values
c_factor_intermediate = intermediate_df['c_factor'].values
d_factor_intermediate = intermediate_df['d_factor'].values
r_factor_intermediate = intermediate_df['r_factor'].values

# GraphMetrics calculations
b_factor_over_n = b_factor / n
b_factor_over_sqrt_n = b_factor / np.sqrt(n)
u_factor_over_n = u_factor / n
c_factor_over_n = c_factor / n
c_factor_over_n_log_n = c_factor / (n * np.log(n))
c_factor_over_n_squared = c_factor / (n ** 2)
d_factor_over_n = d_factor / n
d_factor_over_n_log_n = d_factor / (n * np.log(n))
d_factor_over_n_squared = d_factor / (n ** 2)
r_factor_over_n = r_factor / n
r_factor_over_n_log_n = r_factor / (n * np.log(n))
r_factor_over_n_log_log_n = r_factor / (n * np.log(np.log(n)))

# Plotting
plots = [
    ("b_factor_vs_n", n, b_factor, n_intermediate, b_factor_intermediate,
        r"$b(n)$", r"$n$", r"$b(n)$"),
    ("b_factor_over_n_vs_n", n, b_factor_over_n, n_intermediate, b_factor_intermediate / n_intermediate,
     r"$\frac{b(n)}{n}$", r"$n$", r"$\frac{b(n)}{n}$"),
    ("b_factor_over_sqrt_n_vs_n", n, b_factor_over_sqrt_n, n_intermediate, b_factor_intermediate / np.sqrt(n_intermediate),
     r"$\frac{b(n)}{\sqrt{n}}$", r"$n$", r"$\frac{b(n)}{\sqrt{n}}$"),
    ("u_factor_over_n_vs_n", n, u_factor_over_n, n_intermediate, u_factor_intermediate / n_intermediate,
     r"$\frac{u(n)}{n}$", r"$n$", r"$\frac{u(n)}{n}$"),
    ("u_factor_vs_n", n, u_factor, n_intermediate, u_factor_intermediate,
        r"$u(n)$", r"$n$", r"$u(n)$"),
    ("c_factor_over_n_vs_n", n, c_factor_over_n, n_intermediate, c_factor_intermediate / n_intermediate,
     r"$\frac{c(n)}{n}$", r"$n$", r"$\frac{c(n)}{n}$"),
    ("c_factor_over_n_log_n_vs_n", n, c_factor_over_n_log_n, n_intermediate, c_factor_intermediate / (n_intermediate * np.log(n_intermediate)),
     r"$\frac{c(n)}{n \log n}$", r"$n$", r"$\frac{c(n)}{n \log n}$"),
    ("c_factor_over_n_squared_vs_n", n, c_factor_over_n_squared, n_intermediate, c_factor_intermediate / (n_intermediate ** 2),
     r"$\frac{c(n)}{n^2}$", r"$n$", r"$\frac{c(n)}{n^2}$"),
    ("c_factor_vs_n", n, c_factor, n_intermediate, c_factor_intermediate,
        r"$c(n)$", r"$n$", r"$c(n)$"),
    ("d_factor_over_n_vs_n", n, d_factor_over_n, n_intermediate, d_factor_intermediate / n_intermediate,
     r"$\frac{d(n)}{n}$", r"$n$", r"$\frac{d(n)}{n}$"),
    ("d_factor_over_n_log_n_vs_n", n, d_factor_over_n_log_n, n_intermediate, d_factor_intermediate / (n_intermediate * np.log(n_intermediate)),
     r"$\frac{d(n)}{n \log n}$", r"$n$", r"$\frac{d(n)}{n \log n}$"),
    ("d_factor_over_n_squared_vs_n", n, d_factor_over_n_squared, n_intermediate, d_factor_intermediate / (n_intermediate ** 2),
     r"$\frac{d(n)}{n^2}$", r"$n$", r"$\frac{d(n)}{n^2}$"),
    ("d_factor_vs_n", n, d_factor, n_intermediate, d_factor_intermediate,
        r"$d(n)$", r"$n$", r"$d(n)$"),
    ("r_factor_over_n_vs_n", n, r_factor_over_n, n_intermediate, r_factor_intermediate / n_intermediate,
     r"$\frac{r(n)}{n}$", r"$n$", r"$\frac{r(n)}{n}$"),
    ("r_factor_over_n_log_n_vs_n", n, r_factor_over_n_log_n, n_intermediate, r_factor_intermediate / (n_intermediate * np.log(n_intermediate)),
     r"$\frac{r(n)}{n \log n}$", r"$n$", r"$\frac{r(n)}{n \log n}$"),
    ("r_factor_over_n_log_log_n_vs_n", n, r_factor_over_n_log_log_n, n_intermediate, r_factor_intermediate / (n_intermediate * np.log(np.log(n_intermediate))),
     r"$\frac{r(n)}{n \log \log n}$", r"$n$", r"$\frac{r(n)}{n \log \log n}$"),
    ("r_factor_vs_n", n, r_factor, n_intermediate, r_factor_intermediate,
        r"$r(n)$", r"$n$", r"$r(n)$"),
]

# Generate and save each plot
for plot_name, x, y, x_scatter, y_scatter, ylabel, xlabel, legend_label in plots:
    plt.figure(figsize=(6, 6))
    plt.plot(x, y, label=f"Average", zorder=2, color='red')
    plt.scatter(x_scatter, y_scatter, label=f"Single", color='pink', s=1)
    plt.title(f"{ylabel} vs {xlabel}")
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"graphs/{plot_name}.png", dpi=300)
    plt.close()
