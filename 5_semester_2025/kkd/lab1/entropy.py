import sys
import math
from collections import Counter, defaultdict

debug = False
if "--debug" in sys.argv:
    debug = True
    sys.argv.remove("--debug")

if len(sys.argv) < 2:
    print("Usage: python entropy.py <filename>")
    sys.exit(1)

filename = sys.argv[1]
file = open(filename, "rb").read()
file_len = len(file)

## -- utils --

print_uint8 = lambda char: chr(char) if 32 <= char <= 126 else '?'

## -- basic probability --

counter = dict(Counter(file))
for k in counter.keys():
    counter[k] = counter[k]/file_len

for k, v in sorted(counter.items(), key=lambda item: item[1], reverse=True):
    if debug:
        print(f"P({str(k).zfill(3)}) = {v:.8f}")

## -- conditional probability -- 

## first   - x
## second  - y

pair_counter = defaultdict(int)
total_counter = defaultdict(int)

for i in range(len(file) - 1):
    first = file[i]
    second = file[i + 1]
    pair_counter[(first, second)] += 1
    total_counter[first] += 1

for (condition, value), count in pair_counter.items():
    prob = count / total_counter[condition]
    pair_counter[(condition, value)] = prob 

    if debug:
        print(f"P({str(second).zfill(3)}|{str(condition).zfill(3)}) ({print_uint8(condition)}->{print_uint8(value)}): {prob:.8f}")

## wikipedia = https://en.wikipedia.org/wiki/Entropy_(information_theory)
## -- calculate H(X) = -sum_{x in X} p(x) log p(x)

H_X = 0
for v in counter.values(): 
    H_X += v * -math.log2(v)

print(f"H(X) = {H_X:.8f}")

## -- calculate H(Y|X) --
## I(y|x) = -log2(P(y|x))

H_YX = 0
for condition in counter.keys():
    H_Yx = 0
    for value in counter.keys():
        prob = pair_counter.get((condition, value), 0)
        if prob > 0:
            H_Yx += prob * -math.log2(prob)
    H_YX += counter[condition] * H_Yx

print(f"H(Y|X) = {H_YX:.8f}")