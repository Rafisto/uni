import os
import matplotlib.pyplot as plt

data_dir = "../results/"

plt.figure(figsize=(10, 6))

colors = {
    "dial.m": "blue",
    "dial.r": "cyan",
    "dijkstra.m": "red",
    "dijkstra.r": "orange",
    "radix_heap.m": "green",
    "radix_heap.r": "lightgreen",
}

def print_stats(ffunc, s, e):
    plt.title(f"Wykres czasu od $i$ dla {ffunc('').split('.')[0][:-1]}")
    data = []
    for i in range(s, e, 1):
        file_name = ffunc(i)
        file_path = os.path.join(data_dir, file_name)
        
        if not os.path.exists(file_path):
            data.append(None)
            continue

        with open(file_path, "r") as f:
            for line in f:
                if line.startswith("t"):
                    data.append(float(line.split()[1]))

    data = list(zip(range(s, e), data))
    x, y = zip(*data)
    color_key = '.'.join(ffunc('').split('.')[1:3])
    print(color_key)
    color = colors.get(color_key, "black")  # Default to black if no color is found

    if ffunc('').endswith('.m'):
        plt.plot(x, y, marker='x', linestyle='--', color=color, label=f"{ffunc('')}in")
    else:  
        plt.plot(x, y, marker='o', color=color, label=f"{ffunc('')}and")

def plot_longc():
    setup_plot()
    print_stats(lambda i: f"longc_{i}.dijkstra.r", 0, 16)
    print_stats(lambda i: f"longc_{i}.dijkstra.m", 0, 16)
    print_stats(lambda i: f"longc_{i}.radix_heap.r", 0, 16)
    print_stats(lambda i: f"longc_{i}.radix_heap.m", 0, 16)
    print_stats(lambda i: f"longc_{i}.dial.r", 0, 9)
    print_stats(lambda i: f"longc_{i}.dial.m", 0, 9)
    finalize_plot("longc_plot.png")
    plt.ylim(0, 1000)
    finalize_plot("longc_plot_zoomed.png")

def plot_longn():
    setup_plot()
    print_stats(lambda i: f"longn_{i}.dijkstra.r", 10, 22)
    print_stats(lambda i: f"longn_{i}.dijkstra.m", 10, 22)
    print_stats(lambda i: f"longn_{i}.radix_heap.r", 10, 22)
    print_stats(lambda i: f"longn_{i}.radix_heap.m", 10, 22)
    print_stats(lambda i: f"longn_{i}.dial.r", 10, 22)
    print_stats(lambda i: f"longn_{i}.dial.m", 10, 22)
    finalize_plot("longn_plot.png")
    plt.ylim(0, 1000)
    finalize_plot("longn_plot_zoomed.png")

def plot_randomc():
    setup_plot()
    print_stats(lambda i: f"random4c_{i}.dijkstra.r", 0, 16)
    print_stats(lambda i: f"random4c_{i}.dijkstra.m", 0, 16)
    print_stats(lambda i: f"random4c_{i}.radix_heap.r", 0, 16)
    print_stats(lambda i: f"random4c_{i}.radix_heap.m", 0, 16)
    print_stats(lambda i: f"random4c_{i}.dial.r", 0, 16)
    print_stats(lambda i: f"random4c_{i}.dial.m", 0, 16)
    finalize_plot("random4c_plot.png")
    plt.ylim(0, 1000)
    finalize_plot("random4c_plot_zoomed.png")

def plot_randomn():
    setup_plot()
    print_stats(lambda i: f"random4n_{i}.dijkstra.r", 10, 22)
    print_stats(lambda i: f"random4n_{i}.dijkstra.m", 10, 22)
    print_stats(lambda i: f"random4n_{i}.radix_heap.r", 10, 22)
    print_stats(lambda i: f"random4n_{i}.radix_heap.m", 10, 22)
    print_stats(lambda i: f"random4n_{i}.dial.r", 10, 22)
    print_stats(lambda i: f"random4n_{i}.dial.m", 10, 22)
    finalize_plot("random4n_plot.png")
    plt.ylim(0, 1000)
    finalize_plot("random4n_plot_zoomed.png")

def plot_squarec():
    setup_plot()
    print_stats(lambda i: f"squarec_{i}.dijkstra.r", 0, 16)
    print_stats(lambda i: f"squarec_{i}.dijkstra.m", 0, 16)
    print_stats(lambda i: f"squarec_{i}.radix_heap.r", 0, 16)
    print_stats(lambda i: f"squarec_{i}.radix_heap.m", 0, 16)
    print_stats(lambda i: f"squarec_{i}.dial.r", 0, 16)
    print_stats(lambda i: f"squarec_{i}.dial.m", 0, 16)
    finalize_plot("squarec_plot.png")
    plt.ylim(0, 1000)
    finalize_plot("squarec_plot_zoomed.png")

def plot_squaren():
    setup_plot()
    print_stats(lambda i: f"squaren_{i}.dijkstra.r", 10, 22)
    print_stats(lambda i: f"squaren_{i}.dijkstra.m", 10, 22)
    print_stats(lambda i: f"squaren_{i}.radix_heap.r", 10, 22)
    print_stats(lambda i: f"squaren_{i}.radix_heap.m", 10, 22)
    print_stats(lambda i: f"squaren_{i}.dial.r", 10, 22)
    print_stats(lambda i: f"squaren_{i}.dial.m", 10, 22)
    finalize_plot("squaren_plot.png")
    plt.ylim(0, 1000)
    finalize_plot("squaren_plot_zoomed.png")

def plot_usa():
    setup_plot()
    regions = [
        "USA", "BAY", "CAL", "COL", "CTR", "E", "FLA", "LKS", "NE", "NW", "NY", "W"
    ]
    algorithms = ["dial", "dijkstra", "radix_heap"]
    extensions = ["m", "r"]

    x_labels = []
    data_by_algorithm = {alg: [] for alg in algorithms}
    region_means = []

    for region in regions:
        x_labels.append(region)
        region_times = []
        for algorithm in algorithms:
            times = []
            for ext in extensions:
                if region == "USA":
                    file_name = f"usa.{algorithm}.{ext}"
                else:
                    file_name = f"USA-road-d.{region}.gr.{algorithm}.{ext}"
                file_path = os.path.join(data_dir, file_name)
                
                if os.path.exists(file_path):
                    with open(file_path, "r") as f:
                        for line in f:
                            if line.startswith("t"):
                                times.append(float(line.split()[1]))
            avg_time = sum(times) / len(times) if times else 0
            data_by_algorithm[algorithm].append(avg_time)
            region_times.append(avg_time)
        region_means.append((region, sum(region_times) / len(region_times) if region_times else 0))

    sorted_regions = sorted(region_means, key=lambda x: x[1])
    sorted_indices = [regions.index(region) for region, _ in sorted_regions]
    x_labels = [region for region, _ in sorted_regions]

    x = range(len(regions))
    width = 0.2
    offsets = [-width, 0, width]

    for i, (algorithm, offset) in enumerate(zip(algorithms, offsets)):
        sorted_data = [data_by_algorithm[algorithm][idx] for idx in sorted_indices]
        plt.bar(
            [pos + offset for pos in x],
            sorted_data,
            width=width,
            label=algorithm
        )

    plt.title("Czas wykonania algorytmów dla regionów USA")
    plt.xlabel("Region")
    plt.ylabel("Średni czas wykonania [ms]")
    plt.xticks(x, x_labels, rotation=45)
    plt.legend()
    finalize_plot("usa_bar_chart.png")

def setup_plot():
    plt.clf()
    plt.xlabel("Wartość $i$")
    plt.ylabel("Czas wykonania [ms]")
    plt.grid()

def finalize_plot(fname):
    plt.legend()
    plt.savefig(fname)

if __name__ == "__main__":
    plot_longc()
    plot_longn()
    plot_randomc()
    plot_randomn()
    plot_squarec()
    plot_squaren()
    plot_usa()