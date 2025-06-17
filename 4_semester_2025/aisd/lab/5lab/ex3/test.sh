#!/bin/bash

for i in {1..5}; do
    ./test.out results${i}.csv &
done
wait
for i in {1..5}; do
    python _test_plot.py results${i}.csv &
done
wait

# zero results.csv
> results.csv

for i in {1..5}; do
    for N in {100..10000..100}; do
        echo "Testing with N=$N (Run $i)"
        OUTPUT=$(./main.out $N)
        TOTAL_COMPARISONS=$(echo "$OUTPUT" | grep 'Total comparisons' | awk '{print $3}')
        if [[ -n "$TOTAL_COMPARISONS" ]]; then
            echo "$N;$TOTAL_COMPARISONS" >> results.csv
        fi
    done
done

python _plot_results.py results.csv
