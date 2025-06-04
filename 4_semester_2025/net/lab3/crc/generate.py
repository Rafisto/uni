#!/usr/bin/env python3

import sys
import random

def generate_random_bits(n_bits):
    return ''.join(random.choice('01') for _ in range(n_bits))

def main():
    if len(sys.argv) < 2:
        print("Usage: genbits.py <n_bits>")
        sys.exit(1)

    try:
        n_bits = int(sys.argv[1])
    except ValueError:
        print("Error: number of bits must be an integer.")
        sys.exit(1)

    bits = generate_random_bits(n_bits)
    print(bits)

if __name__ == "__main__":
    main()
