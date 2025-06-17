import sys
import pandas as pd
import matplotlib.pyplot as plt


def plot_results(results_file):
    data = pd.read_csv(results_file)

    aggregated_data = data.groupby('Graph Size', as_index=False).agg(
        Min_Rounds=('Rounds', 'min'),
        Max_Rounds=('Rounds', 'max'),
        Average_Rounds=('Rounds', 'mean')
    )

    plt.figure(figsize=(10, 6))

    plt.fill_between(
        aggregated_data['Graph Size'],
        aggregated_data['Min_Rounds'],
        aggregated_data['Max_Rounds'],
        color='lightblue',
        alpha=0.5,
        label='Range (Min to Max)'
    )
    plt.plot(aggregated_data['Graph Size'], 
             aggregated_data['Average_Rounds'],
             label='Average Rounds', 
             color='blue',
             marker='o')

    plt.title('Rounds vs Graph Size (Aggregated)')
    plt.xlabel('Graph Size')
    plt.ylabel('Number of Rounds')
    plt.legend()
    plt.grid(True)

    plt.savefig('results.png')
    plt.show()


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 plot.py <results_file>")
        sys.exit(1)

    results_file = sys.argv[1]
    plot_results(results_file)
