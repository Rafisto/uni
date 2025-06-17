import sys
import pandas as pd
import matplotlib.pyplot as plt

def plot_xy(file_path):
    data = pd.read_csv(file_path, sep=';', header=None, names=['category', 'x', 'y'])

    category_colors = {
        'keys1': "#E136CA",
        'keys2': "#3AE637",
        'union': "#E8304B",
        'emin': "#464EF0"
    }
    colors = data['category'].map(category_colors).fillna('gray')

    plt.figure(figsize=(10, 6))
    plt.bar(data['x'], data['y'], color=colors, width=0.8, align='center')
    plt.title('Histogram of y vs x (colored by category)')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(axis='y')

    handles = [plt.Rectangle((0,0),1,1, color=category_colors[c]) for c in category_colors]
    plt.legend(handles, category_colors.keys())

    plt.savefig(file_path.replace('.csv', '.png'), dpi=300)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python plot.py <csv_file>")
        sys.exit(1)
    plot_xy(sys.argv[1])
