from collections import Counter, defaultdict
import math
from bitstream import BitStream
from fibonacci import Fibonacci
from elias import Elias
import argparse


def lzw_encode(input_file, output_file, cfunc, coding):
    with open(input_file, 'rb') as infile, open(output_file, 'wb') as outfile:
        data = infile.read()
        dict_size = 256
        dictionary = {bytes([i]): i for i in range(dict_size)}

        if not data:
            return
        P = bytes([data[0]])

        result = []
        for byte in data[1:]:
            C = bytes([byte])
            # longer prefix already exists, search further
            if P + C in dictionary:
                P = P + C
            # new prefix, add to dictionary
            else:
                result.append(dictionary[P])
                dictionary[P + C] = dict_size
                dict_size += 1
                P = C
        if P:
            result.append(dictionary[P])

        bit_stream = BitStream()
        for code in result:
            code += 1
            res_b = cfunc(code)
            bit_stream.join(res_b)

        bits = bit_stream.to01()

        pad_len = (8 - len(bits) % 8) % 8
        if pad_len:
            if coding == "omega":
                bits += '1' * pad_len
            else:
                bits += '0' * pad_len

        out_bytes = int(bits, 2).to_bytes(
            (len(bits) + 7) // 8, byteorder='big')
        outfile.write(out_bytes)


def lzw_decode(input_file, output_file, dfunc, coding):
    with open(input_file, 'rb') as infile, open(output_file, 'wb') as outfile:
        data = infile.read()
        if not data:
            return

        bits = bin(int.from_bytes(data, byteorder='big'))[2:]

        if coding in ["omega", "fibonacci"]:
            total_len = len(data) * 8
            bits = bits.zfill(total_len)
            i = len(bits) - 1
            if coding == "omega":
                while i >= 0 and bits[i] == '1':
                    i -= 1
                if i >= 0:
                    bits = bits[:i + 1]
            if coding == "fibonacci":
                while i >= 1:
                    if bits[i] == '1' and bits[i - 1] == '1':
                        bits = bits[:i + 1]
                        break
                    i -= 1
        else:
            bits = bits.zfill(len(data) * 8)

        bit_stream = BitStream(bits)
        codes = []
        while not bit_stream.empty():
            code = dfunc(bit_stream)
            if code is None:
                break
            codes.append(code - 1)

        dict_size = 256
        dictionary = {i: bytes([i]) for i in range(dict_size)}

        if not codes:
            return

        P = codes[0]
        S = dictionary[P]
        outfile.write(S)
        # output first byte
        for C in codes[1:]:
            # new character, difficult case
            if C not in dictionary:
                entry = dictionary[P] + dictionary[P][:1]
            # found then return
            else:
                entry = dictionary[C]
            outfile.write(entry)
            dictionary[dict_size] = dictionary[P] + entry[:1]
            dict_size += 1
            P = C


def stats(input_file, output_file):
    in_size = 0
    out_size = 0
    with open(input_file, "rb") as f:
        file = f.read()
        in_size = len(file)
        if len(file) == 0:
            print("INPUT empty.")
        else:
            ctr = dict(Counter(file))
            counter = defaultdict(float)
            for k in ctr.keys():
                counter[k] = ctr[k]/len(file)
            H_X = 0.0
            for v in counter.values():
                if v > 0:
                    H_X += v * -math.log2(v)
            print(f"INPUT: H(X) = {H_X:.8f}")

    with open(output_file, "rb") as f:
        data = f.read()
        out_size = len(data)
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

    print(
        f"Compression Ratio: {round((in_size-out_size)*100/in_size, 4)}% {in_size} -> {out_size} bytes")
    print(
        f"Average symbol length: {round(out_size*8/in_size, 4)} bits/symbol")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="LZW")
    parser.add_argument("mode", choices=["encode", "decode"])
    parser.add_argument("input_file", help="Input file")
    parser.add_argument("output_file", help="Output file")
    parser.add_argument("--coding", choices=["gamma", "delta", "omega",
                        "fibonacci"], default="omega", help="default=omega")

    args = parser.parse_args()

    functions = {
        "gamma": (Elias.gamma_encode, Elias.gamma_decode),
        "delta": (Elias.delta_encode, Elias.delta_decode),
        "omega": (Elias.omega_encode, Elias.omega_decode),
        "fibonacci": (Fibonacci.encode, Fibonacci.decode),
    }

    pretty = {
        "gamma": "\x1b[38;2;255;0;0mElias gamma\x1b[0m",
        "delta": "\x1b[38;2;0;128;255mElias delta\x1b[0m",
        "omega": "\x1b[38;2;0;255;0mElias omega\x1b[0m",
        "fibonacci": "\x1b[38;2;255;215;0mFibonacci\x1b[0m",
    }

    if args.mode == "encode":
        print(f"\x1b[1m{pretty[args.coding]} :: \x1b[1mFile: {args.input_file}\x1b[0m")
        print(
            f"mode={args.mode}, coding={args.coding}, coding_func={functions[args.coding][0].__name__}")
        lzw_encode(args.input_file, args.output_file,
                   functions[args.coding][0], args.coding)
        stats(args.input_file, args.output_file)
    else:
        lzw_decode(args.input_file, args.output_file,
                   functions[args.coding][1], args.coding)
