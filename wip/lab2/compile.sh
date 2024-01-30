#!/bin/bash

for i in {1..5}
do
    echo "Building zadanie${i}.c"
    clang -Wextra -lm --pedantic -std=c11 -o "zadanie${i}" "zadanie${i}.c"
done
