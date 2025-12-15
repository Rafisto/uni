# Rafał Włodarczyk 279762
from bitstream import BitStream

fib = [1, 2]
for _ in range(44):
    fib.append(fib[-1] + fib[-2])

class Fibonacci:
    @staticmethod
    def encode(n: int) -> BitStream:
        coeffs = [0] * len(fib)
        numLen = 1
        while n - fib[numLen - 1] >= fib[numLen]:
            numLen += 1
        if n == 1:
            numLen = 0
        j = numLen
        num = n
        while num:
            if num >= fib[j]:
                coeffs[j] = 1
                num -= fib[j]
            j -= 1
        bits = BitStream()
        for j in range(numLen + 1):
            bits.write_bit(coeffs[j])
        bits.write_bit(1)
        return bits

    @staticmethod
    def decode(bits: BitStream) -> int:
        num = 0
        i = 0
        prev = 0
        while not bits.empty():
            bit = bits.read_bit()
            if bit == None:
                break
            if prev == 1 and bit == 1:
                return num
            num += bit * fib[i]
            prev = bit
            i += 1
        return num 
