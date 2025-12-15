from bitstream import BitStream

class Elias:

    # Elias γ-encoding
    @staticmethod
    def gamma_encode(x: int):
        """
        (n-1 zeros)(x in binary)
        """
        if x <= 0:
            raise ValueError("cannot encode <=0")

        n = x.bit_length()
        arr = BitStream()
        for _ in range(n - 1):
            arr.write_bit(0)
        arr.write_bits(x, n)
        return arr

    # Elias γ-decoding
    @staticmethod
    def gamma_decode(bitstream: BitStream) -> int | None:
        n = 0
        while bitstream.read_bit() == 0:
            if bitstream.empty():
                return None
            n += 1
        value = 1 << n
        for i in range(n):
            b = bitstream.read_bit()
            if b is None:
                return None
            value |= (b << (n - 1 - i))
        return value

    # Elias δ-encoding

    @staticmethod
    def delta_encode(x: int):
        """
        (k-1 zeros)(n to binary)(x to binary without leading 1)
        k = bit length of n
        """
        if x <= 0:
            raise ValueError("cannot encode <=0")

        n = x.bit_length()
        k = n.bit_length()
        arr = BitStream()
        for _ in range(k - 1):
            arr.write_bit(0)
        arr.write_bits(n, k)
        arr.write_bits(x - (1 << (n - 1)), n - 1)
        return arr

    # Elias δ-decoding
    @staticmethod
    def delta_decode(bitstream: BitStream) -> int | None:
        k = 0
        while bitstream.read_bit() == 0:
            if bitstream.empty():
                return None
            k += 1
        n = 1 << k
        for i in range(k):
            b = bitstream.read_bit()
            if b is None:
                return None
            n |= (b << (k - 1 - i))
        value = 1 << (n - 1)
        for i in range(n - 1):
            b = bitstream.read_bit()
            if b is None:
                return None
            value |= (b << (n - 2 - i))
        return value

    # Elias ω-encoding
    @staticmethod
    def omega_encode(x: int) -> BitStream:
        """

        """
        if x <= 0:
            raise ValueError("Cannot encode non-positive integers")

        code = [0]
        while x > 1:
            binary = [int(b) for b in bin(x)[2:]]
            code = binary + code 
            x = len(binary) - 1
        return BitStream(''.join(map(str, code)))

    # Elias ω-decoding
    @staticmethod
    def omega_decode(bitstream: BitStream) -> int | None:
        value = 1
        while True:
            bit = bitstream.read_bit()
            if bit == None:
                return None
            if bit == 0:
                return value
            n = 1
            for _ in range(value):
                b = bitstream.read_bit()
                if b is None:
                    return None
                n = (n << 1) | b
            value = n
