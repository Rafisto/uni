import sys
import pandas as pd
import matplotlib.pyplot as plt

def plot_n_vs_data_per_n(file_path):
    data = pd.read_csv(file_path, sep=';', header=0, names=['N', 'data'])
    grouped_data = data.groupby('N', as_index=False).mean()
    grouped_data['data_per_N'] = grouped_data['data'] / grouped_data['N']

    plt.figure(figsize=(10, 6))
    plt.plot(grouped_data['N'], grouped_data['data_per_N'], marker='o')
    plt.title('Plot data/N vs N (Averaged)')
    plt.xlabel('N')
    plt.ylabel('data/N')
    plt.grid(True)

    plt.savefig(file_path.replace('.csv', '_over_n_vs_n_averaged.png'), dpi=300)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python finalplot.py <csv_file>")
        sys.exit(1)
    plot_n_vs_data_per_n(sys.argv[1])
