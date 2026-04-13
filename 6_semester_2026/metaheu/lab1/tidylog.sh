#!/bin/bash
sed -i "s/^\[.*//" task*.res
sed -i "s/Progress.*//" task*.res
sed -i "s/tsp\\n/tsp/" task*.res
sed -i '/^[[:space:]]*$/d' task*.res