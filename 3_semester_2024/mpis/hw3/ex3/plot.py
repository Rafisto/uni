import pandas as pd
import matplotlib.pyplot as plt
import os
import numpy as np

# Ensure the output directory exists
os.makedirs("graphs", exist_ok=True)

# Load the data
df = pd.read_csv('star_network_results.csv')

grouped = df.groupby(['n', 'p'])['rounds'].mean().unstack()

n = grouped.index
p_values = grouped.columns
rounds_mean = grouped.values

n_full = df['n']
rounds_full = df['rounds']
p_full = df['p']

# Plot settings
for p in p_values:
    p_data = df[df['p'] == p]
    
    plt.figure(figsize=(6, 6))
    plt.scatter(p_data['n'], p_data['rounds'], label=f"rounds for p={p}", color='blue', s=1)
    plt.scatter(n, rounds_mean[:, p_values.get_loc(p)], label=f"average rounds for p={p}", color='red', marker='o', s=2)
    
    plt.title(f"Rounds vs n for p={p}")
    plt.xlabel(r"$n$")
    plt.ylabel(r"Rounds")
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"graphs/rounds_vs_n_p{p}.png", dpi=300)
    plt.close()

# plt.figure(figsize=(6, 6))
# for p in p_values:
#     plt.plot(n, rounds_mean[:, p_values.get_loc(p)], label=f"avg rounds for p={p}", marker='o', markersize=3)

# plot Rounds vs n for p = 0.1 divided by log(n)

plt.title("Rounds vs n divided by log(n) and sqrt(n)")
plt.xlabel(r"$n$")
plt.ylabel(r"Rounds")
for p in p_values:
    # div by log(n)
    plt.plot(n, rounds_mean[:, p_values.get_loc(p)] / np.log(n), label=f"avg rounds/log(n) for p={p}", marker='o', markersize=3)
    # dib by sqrt(n)
    plt.plot(n, rounds_mean[:, p_values.get_loc(p)] / np.sqrt(n), label=f"avg rounds/sqrt(n) for p={p}", marker='o', markersize=3)

plt.legend()
plt.tight_layout()
plt.savefig("graphs/rounds_vs_n_div_log_n.png", dpi=300)
plt.close()