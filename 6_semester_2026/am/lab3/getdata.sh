#!/bin/bash
# https://www.math.uwaterloo.ca/tsp/world/countries.html

mkdir -p data

# lab0

wget https://www.math.uwaterloo.ca/tsp/world/wi29.tsp -O data/western_sahara.tsp
wget https://www.math.uwaterloo.ca/tsp/world/dj38.tsp -O data/djibouti.tsp
wget https://www.math.uwaterloo.ca/tsp/world/qa194.tsp -O data/qatar.tsp
wget https://www.math.uwaterloo.ca/tsp/world/uy734.tsp -O data/uruguay.tsp
wget https://www.math.uwaterloo.ca/tsp/world/zi929.tsp -O data/zimbabwe.tsp

# lab1, lab2, lab3

wget https://www.math.uwaterloo.ca/tsp/world/mu1979.tsp -O data/oman.tsp
wget https://www.math.uwaterloo.ca/tsp/world/ca4663.tsp -O data/canada.tsp
wget https://www.math.uwaterloo.ca/tsp/world/tz6117.tsp -O data/tanzania.tsp
wget https://www.math.uwaterloo.ca/tsp/world/eg7146.tsp -O data/egypt.tsp
wget https://www.math.uwaterloo.ca/tsp/world/ei8246.tsp -O data/ireland.tsp
