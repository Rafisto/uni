#!/bin/bash
sed -i "s/^\[.*//" tabu.res
sed -i "s/Progress.*//" tabu.res
sed -i "s/tsp\\n/tsp/" tabu.res
sed -i '/^[[:space:]]*$/d' tabu.res
sed -i "/MST.*/d" tabu.res