#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 <number_of_tests> <bsize>"
    exit 1
fi

NUM_TESTS=$1
BSIZE=$2

echo "RC1;RC2;Input;Packets;Returned" > results.csv

NUM_PROCS=16
for ((i=1; i<=NUM_TESTS; i+=NUM_PROCS)); do
    for ((j=0; j<NUM_PROCS; j++)); do
        if ((i + j <= 100)); then
            (
                INPUT=$(python3 generate.py "${BSIZE}")

                OUTPUT=$(python3 main.py b "$INPUT")

                PACKETS=$(echo "$OUTPUT" | tail -n 1)
                RC1=$?

                RETURNED=$(python3 main.py t "$PACKETS" | tail -n 1)
                RC2=$?

                echo "$RC1;$RC2;$INPUT;$PACKETS;$RETURNED" >> results.csv

                if [ "$RC1" -eq 0 ] && [ "$RC2" -eq 0 ] && [ "$RETURNED" == "$INPUT" ]; then
                    echo -ne "\e[32m$((i + j))\e[0m,"
                else
                    echo -ne "\e[31m$((i + j))\e[0m,"
                fi
            ) &
        fi
    done
    wait
done

echo -e "\nDone"
