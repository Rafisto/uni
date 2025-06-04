import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import matplotlib.ticker as ticker
import numpy as np

df = pd.read_csv("output.txt")

df['testname'] = df['testname'].str.replace('"', '')
df['operation'] = df['testname'].apply(
    lambda x: 'insert' if 'inserts' in x else 'delete')
df['key_order'] = df['testname'].apply(
    lambda x: 'random' if 'random' in x else 'ascending')

grouped = df.groupby(['testname', 'N', 'ds', 'key_order', 'operation']).agg({
    'average_comparisons': 'mean',
    'max_comparisons': 'max',
    'average_pointer_operations': 'mean',
    'max_pointer_operations': 'max',
    'average_tree_height': 'mean',
    'max_tree_height': 'max',
    'average_cost': 'mean',
    'max_cost': 'max'
}).reset_index()

df = grouped

plt.rcParams.update({
    'font.family': 'serif',
    'font.size': 12,
    'axes.titlesize': 14,
    'axes.labelsize': 13,
    'legend.fontsize': 11,
    'xtick.labelsize': 11,
    'ytick.labelsize': 11,
    'text.usetex': False
})
sns.set(style="whitegrid")

markers = {
    ('random', 'insert'): 'o',
    ('random', 'delete'): 's',
    ('ascending', 'insert'): '^',
    ('ascending', 'delete'): 'D',
}

colors = sns.color_palette("muted")


def plot_metric(metric_base, ylabel, output_filename_base):
    fig, ax = plt.subplots(figsize=(6, 4.5))

    for idx, (key_order, operation) in enumerate(markers.keys()):
        subset = df[(df['key_order'] == key_order) & (
            df['operation'] == operation)].sort_values("N")
        label = f"{key_order.capitalize()} {operation}s"
        ax.plot(
            subset['N'],
            subset[f'average_{metric_base}'],
            marker=markers[(key_order, operation)],
            linestyle='-',
            label=label,
            color=colors[idx],
            linewidth=1.5,
            markersize=5
        )
        ax.fill_between(
            subset['N'],
            subset[f'average_{metric_base}'],
            subset[f'max_{metric_base}'],
            color=colors[idx],
            alpha=0.2,
            linewidth=0
        )

    ax.set_title(f"{ylabel} vs $N$ (ds={df['ds'][0]})")
    ax.set_xlabel("$N$ (Max Tree Size)")
    ax.set_ylabel(ylabel)
    ax.set_yscale('log')

    ax.grid(which='major', linestyle='--', linewidth=0.5, alpha=0.7)
    ax.grid(which='minor', linestyle=':', linewidth=0.5, alpha=0.5)
    ax.tick_params(axis='both', which='both',
                   direction='in', top=True, right=True)

    fig.legend(
        loc='lower center',
        bbox_to_anchor=(0.5, 0),
        ncol=2,
        frameon=False
    )

    fig.tight_layout()
    fig.subplots_adjust(bottom=0.25)
    fig.savefig(f"{output_filename_base}.png", dpi=300,
                bbox_inches='tight', format='png')
    plt.close(fig)


plot_metric("comparisons", "Average Comparisons", "_comparisons_vs_N")
plot_metric("pointer_operations", "Average Pointer Operations",
            "_pointer_operations_vs_N")
plot_metric("tree_height", "Average Tree Height", "_tree_height_vs_N")
plot_metric("cost", "Average Cost", "_cost_vs_N")
