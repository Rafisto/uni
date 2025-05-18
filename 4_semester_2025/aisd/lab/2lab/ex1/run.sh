#!/bin/bash

# Generators:
# - generator_ascending
# - generator_descending
# - generator_random
#
# Sorters:
# - insertion_sort
# - quick_sort
# - hybrid_sort

make clean
make

lengths=(8 32)
generators=(generator_ascending generator_descending generator_random)
sorters=(insertion_sort quick_sort hybrid_sort)

for length in ${lengths[@]}; do
    for generator in ${generators[@]}; do
        for sorter in ${sorters[@]}; do
            echo "[+] Running case [gen=${generator}][sort=${sorter}][n=${length}]"
            "./${generator}" $length | "./${sorter}"
            echo
        done
    done
done
