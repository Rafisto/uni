#!/bin/bash

# Example usage:
# ./prims.out 8 | python example_draw.py

start=1000
end=10000
step=1000
repetitions=10

prims_output="_results_prims.txt"
kruskal_output="_results_kruskal.txt"

# zero the files
> "$prims_output"
> "$kruskal_output"

for ((n=start; n<=end; n+=step)); do
    echo "Testing with n=$n"

    echo "n=$n" >> "$prims_output"
    for ((i=1; i<=repetitions; i++)); do
        echo "Prim's algorithm iteration $i for n=$n"
        perf stat ./prims.out "$n" --no-print 2>> "$prims_output"
    done

    echo "n=$n" >> "$kruskal_output"
    for ((i=1; i<=repetitions; i++)); do
        echo "Kruskal's algorithm iteration $i for n=$n"
        perf stat ./kruskal.out "$n" --no-print 2>> "$kruskal_output"
    done

    wait
done

# python plot_results.py