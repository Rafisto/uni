#!/bin/bash

RESULTS_FILE="results.csv"
PLOTS_SCRIPT="plot.py"
K=10

echo "Graph Size,Rounds" > "$RESULTS_FILE"

for graph_size in {0..10000..100}; do
    echo "Processing graph size: $graph_size"

    if [ "$graph_size" -eq 0 ]; then
        echo "0,0" >> "$RESULTS_FILE"
        continue
    fi
    
    for ((i=1; i<=K; i++)); do
        echo "iteration=$i for graph size n=$graph_size"
        ROUNDS=$(./graph.out $graph_size | grep "Number of rounds: " | awk '{print $4}')
        
        echo "$graph_size,$ROUNDS" >> "$RESULTS_FILE"
    done
done

if [ -f "$PLOTS_SCRIPT" ]; then
    python3 "$PLOTS_SCRIPT" "$RESULTS_FILE"
else
    echo "Plot script not found. Results saved to $RESULTS_FILE."

fi
