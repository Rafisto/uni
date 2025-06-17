import re
import matplotlib.pyplot as plt

def parse_results(filename):
    times = {}
    cycles = {}
    current_n = None
    with open(filename) as f:
        for line in f:
            line = line.strip()
            if line.startswith("n="):
                current_n = int(line.split("=")[1])
                if current_n not in times:
                    times[current_n] = []
                    cycles[current_n] = []
            elif "seconds time elapsed" in line:
                time_sec = float(line.split()[0])
                times[current_n].append(time_sec)
            elif "cycles" in line:
                cycle_count = int(line.split()[0].replace(',', ''))
                cycles[current_n].append(cycle_count)
    return times, cycles

prims_file = "_results_prims.txt"
kruskal_file = "_results_kruskal.txt"

prims_times, prims_cycles = parse_results(prims_file)
kruskal_times, kruskal_cycles = parse_results(kruskal_file)

def average(lst):
    if len(lst) == 0:
        return 0
    return sum(lst) / len(lst)

ns = sorted(prims_times.keys())
prims_avg_times = [average(prims_times[n]) for n in ns]
kruskal_avg_times = [average(kruskal_times[n]) for n in ns]
prims_avg_cycles = [average(prims_cycles[n]) for n in ns]
kruskal_avg_cycles = [average(kruskal_cycles[n]) for n in ns]


plt.figure(figsize=(10,6))
plt.plot(ns, prims_avg_times, marker='o', label="Prim's Algorithm (Time)")
plt.plot(ns, kruskal_avg_times, marker='s', label="Kruskal's Algorithm (Time)")
plt.xlabel("Input size (n)")
plt.ylabel("Average elapsed time (seconds)")
plt.title("Performance comparison of Prim's and Kruskal's MST algorithms (Time)")
plt.suptitle("Data collected using perf tool (https://github.com/brendangregg/perf-tools)", fontsize=10, y=0.95)
plt.legend()
plt.grid(True)
plt.savefig("_results_mst_performance_time.png")

plt.figure(figsize=(10,6))
plt.plot(ns, prims_avg_cycles, marker='o', label="Prim's Algorithm (Cycles)")
plt.plot(ns, kruskal_avg_cycles, marker='s', label="Kruskal's Algorithm (Cycles)")
plt.xlabel("Input size (n)")
plt.ylabel("Average cycles")
plt.title("Performance comparison of Prim's and Kruskal's MST algorithms (cycles)")
plt.suptitle("Data collected using perf tool (https://github.com/brendangregg/perf-tools)", fontsize=10, y=0.95)
plt.legend()
plt.grid(True)
plt.savefig("_results_mst_performance_cycles.png")

plt.figure(figsize=(10,6))
plt.plot(ns, prims_avg_times, marker='o', label="Prim's Algorithm (Time)")
plt.plot(ns, kruskal_avg_times, marker='s', label="Kruskal's Algorithm (Time)")
plt.yscale('log')
plt.xlabel("Input size (n)")
plt.ylabel("Average elapsed time (seconds) [log scale]")
plt.title("Performance comparison of Prim's and Kruskal's MST algorithms (Time)")
plt.suptitle("Data collected using perf tool (https://github.com/brendangregg/perf-tools)", fontsize=10, y=0.95)
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig("_results_mst_performance_time_log.png")

plt.figure(figsize=(10,6))
plt.plot(ns, prims_avg_cycles, marker='o', label="Prim's Algorithm (Cycles)")
plt.plot(ns, kruskal_avg_cycles, marker='s', label="Kruskal's Algorithm (Cycles)")
plt.yscale('log')
plt.xlabel("Input size (n)")
plt.ylabel("Average cycles [log scale]")
plt.title("Performance comparison of Prim's and Kruskal's MST algorithms (Cycles)")
plt.suptitle("Data collected using perf tool (https://github.com/brendangregg/perf-tools)", fontsize=10, y=0.95)
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig("_results_mst_performance_cycles_log.png")
