# AACwS - Adaptive Arithmetic Coding with Scaling
# Rafal Wlodarczyk 29.10.2025

# Key Resources 
# 0. Stanford Implementation of AACwS
# https://web.stanford.edu/class/ee398a/handouts/papers/WittenACM87ArithmCoding.pdf 
# 1. Arithmetic Code Discussion and Implementation 
# https://michaeldipperstein.github.io/arithmetic.html
# 2. Overview for Context-Based Adaptive Binary Arithmetic Coding (H.264/AVC) 
# https://www.bertolami.com/files/cabac_ieee03.pdf 
# 3. Ross Williams compression reference
# http://www.ross.net/compression/

from collections import Counter, defaultdict
from io import BufferedReader, BufferedWriter
import math
import sys
import os
from typing import List

CODE_BITS = 64
MAX_VALUE = (1 << CODE_BITS) - 1

FST_QTR = MAX_VALUE // 4
SND_QTR = MAX_VALUE // 2
TRD_QTR = 3 * FST_QTR

CHAR_COUNT = 256
EOF = CHAR_COUNT + 1
SYMBOLS = EOF

MAX_FREQUENCY = 1 << (CODE_BITS - 2)

FREQUENCY = [0] * (SYMBOLS + 1)
CDF = [0] * (SYMBOLS + 1)

low = 0
high = MAX_VALUE
licznik = 0
value = 0
out_bits_buffer = 0
out_bits_count = 0
in_bits_buffer = 0
in_bits_count = 0

infile : BufferedReader
outfile : BufferedWriter

def read_byte():
    b = infile.read(1)
    if not b:
        return None
    return b[0]

def write_byte(b: int):
    outfile.write(bytes([b & 0xFF]))

def output_bit(bit: int):
    global out_bits_buffer, out_bits_count
    out_bits_buffer = (out_bits_buffer << 1) | (bit & 1)
    out_bits_count += 1
    if out_bits_count == 8:
        write_byte(out_bits_buffer)
        out_bits_buffer = 0
        out_bits_count = 0

def flush_output_bits():
    global out_bits_buffer, out_bits_count
    if out_bits_count != 0:
        write_byte(out_bits_buffer << (8 - out_bits_count))
        out_bits_buffer = 0
        out_bits_count = 0

def input_bit():
    global in_bits_buffer, in_bits_count
    if in_bits_count == 0:
        b = read_byte()
        if b is None:
            in_bits_buffer = 0
            in_bits_count = 8
        else:
            in_bits_buffer = b
            in_bits_count = 8
    in_bits_count -= 1
    return (in_bits_buffer >> in_bits_count) & 1

def start_model():
    for i in range(1, SYMBOLS + 1):
        FREQUENCY[i] = 1
    CDF[0] = 0
    for i in range(1, SYMBOLS + 1):
        CDF[i] = CDF[i - 1] + FREQUENCY[i]

def total_frequency():
    return CDF[SYMBOLS]

def update_model(symbol: int):
    """
    Increment frequency of 'symbol' and update CDF.
    If frequencies exceed MAX_FREQUENCY, scale them down (halve).
    """
    FREQUENCY[symbol] += 1
    for i in range(symbol, SYMBOLS + 1):
        CDF[i] += 1

    if CDF[SYMBOLS] >= MAX_FREQUENCY:
        for j in range(1, SYMBOLS + 1):
            FREQUENCY[j] = (FREQUENCY[j] + 1) // 2
            if FREQUENCY[j] == 0:
                FREQUENCY[j] = 1
        CDF[0] = 0
        for j in range(1, SYMBOLS + 1):
            CDF[j] = CDF[j - 1] + FREQUENCY[j]

def encode_symbol(symbol: int):
    global low, high, licznik

    total = total_frequency()
    rng = high - low + 1

    cdf_low = CDF[symbol - 1]
    sym_freq = FREQUENCY[symbol]

    low_new = low + (rng * cdf_low) // total
    high_new = low + (rng * (cdf_low + sym_freq)) // total - 1

    low, high = low_new, high_new

    while True:
        if high < SND_QTR:
            output_bit(0)
            for _ in range(licznik):
                output_bit(1)
            licznik = 0
            low = low * 2
            high = high * 2 + 1

        elif low >= SND_QTR:
            output_bit(1)
            for _ in range(licznik):
                output_bit(0)
            licznik = 0
            low = (low - SND_QTR) * 2
            high = (high - SND_QTR) * 2 + 1

        elif low >= FST_QTR and high < TRD_QTR:
            licznik += 1
            low = (low - FST_QTR) * 2
            high = (high - FST_QTR) * 2 + 1

        else:
            break

def done_encoding():
    global licznik
    licznik += 1
    if low < FST_QTR:
        output_bit(0)
        for _ in range(licznik):
            output_bit(1)
    else:
        output_bit(1)
        for _ in range(licznik):
            output_bit(0)
    flush_output_bits()

def start_decoding():
    """
    Initialize the global 'value' by reading CODE_BITS bits from input.
    Returns the initialized value (also sets global 'value').
    """
    global value
    value = 0
    for _ in range(CODE_BITS):
        value = (value << 1) | input_bit()
    return value

def decode_symbol():
    """
    Decode next symbol using global low/high/value.
    Returns the decoded symbol.
    Updates global 'value' in place.
    """
    global low, high, value

    total = total_frequency()
    rng = high - low + 1

    cdf_val = ((value - low + 1) * total - 1) // rng

    lo = 1
    hi = SYMBOLS
    while lo < hi:
        mid = (lo + hi) // 2
        if CDF[mid] > cdf_val:
            hi = mid
        else:
            lo = mid + 1
    symbol = lo

    cdf_low = CDF[symbol - 1]
    sym_freq = FREQUENCY[symbol]
    low_new = low + (rng * cdf_low) // total
    high_new = low + (rng * (cdf_low + sym_freq)) // total - 1
    low, high = low_new, high_new

    while True:
        if high < SND_QTR:
            low = low * 2
            high = high * 2 + 1
            value = (value << 1) | input_bit()
        elif low >= SND_QTR:
            low = (low - SND_QTR) * 2
            high = (high - SND_QTR) * 2 + 1
            value = ((value - SND_QTR) << 1) | input_bit()
        elif low >= FST_QTR and high < TRD_QTR:
            low = (low - FST_QTR) * 2
            high = (high - FST_QTR) * 2 + 1
            value = ((value - FST_QTR) << 1) | input_bit()
        else:
            break

    return symbol

def aacws_encode_file(input_path: str, output_path: str):
    global infile, outfile, low, high, licznik

    infile = open(input_path, "rb")
    outfile = open(output_path, "wb")

    length = os.path.getsize(input_path)

    start_model()
    low = 0
    high = MAX_VALUE
    licznik = 0

    i = 0

    while True:
        if i % 1000 == 0:
            print(f"Progress: {i} symbols encoded.", end="\r")

        b = read_byte()
        if b is None:
            symbol = EOF
        else:
            symbol = b + 1

        encode_symbol(symbol)
        update_model(symbol)

        if symbol == EOF:
            break
        i += 1

    done_encoding()
    infile.close()
    outfile.close()
    print()

    try:
        out_length = os.path.getsize(output_path)
        if length > 0:
            print(f"Compression Ratio {round(out_length*100/length,4)}%")
    except Exception:
        pass

    with open(input_path,"rb") as f:
        file = f.read()
        if len(file) == 0:
            print("INPUT empty.")
        else:
            ctr = dict(Counter(file))
            counter : dict = defaultdict(float)
            for k in ctr.keys():
                counter[k] = ctr[k]/len(file)
            H_X = 0.0
            for v in counter.values():
                if v > 0:
                    H_X += v * -math.log2(v)
            print(f"INPUT: H(X) = {H_X:.8f}")

    with open(output_path,"rb") as f:
        data = f.read()
        if len(data) == 0:
            print("OUTPUT empty.")
        else:
            ctr = dict(Counter(data))
            counter.clear()
            for k in ctr.keys():
                counter[k] = ctr[k]/len(data)
            H_X = 0.0
            for v in counter.values():
                if v > 0:
                    H_X += v * -math.log2(v)
            print(f"OUTPUT: H(X) = {H_X:.8f}")

    print("Encoding complete.")

def aacws_decode_file(input_path: str, output_path: str):
    global infile, outfile, low, high, in_bits_count, in_bits_buffer, value

    infile = open(input_path, "rb")
    outfile = open(output_path, "wb")

    start_model()
    low = 0
    high = MAX_VALUE
    in_bits_count = 0
    in_bits_buffer = 0

    start_decoding()

    i = 0

    while True:
        if i % 1000 == 0:
            print(f"Progress: {i} symbols decoded.", end="\r")

        symbol = decode_symbol()
        if symbol == EOF:
            break

        write_byte(symbol - 1)
        update_model(symbol)
        i += 1

    print(f"Progress: {i} symbols decoded.", end="\r")
    infile.close()
    outfile.close()
    print()
    print("Decoding complete.")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python arithmetic_fixed.py <encode|decode> <input_file> <output_file>")
        sys.exit(1)

    mode = sys.argv[1]
    input_file = sys.argv[2]
    output_file = sys.argv[3]

    if mode not in ["encode", "decode"]:
        print("Mode must be 'encode' or 'decode'")
        sys.exit(1)

    if not os.path.isfile(input_file):
        print(f"File {input_file} does not exist")
        sys.exit(1)

    if os.path.isfile(output_file):
        print(f"File {output_file} exists, overwrite? [y/N]")
        ans = input().strip().lower()
        if ans != 'y':
            print("Cancelled.")
            sys.exit(0)

    if mode == "encode":
        aacws_encode_file(input_file, output_file)
    else:
        aacws_decode_file(input_file, output_file)
