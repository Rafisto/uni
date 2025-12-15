class BitStream:
    def __init__(self, bits: str = ''):
        self.bits = [int(b) for b in bits]
        self.pos = 0

    def length(self) -> int:
        return len(self.bits)
        
    def empty(self) -> bool:
        return self.pos >= len(self.bits)
    
    def join(self, other):
        self.bits.extend(other.bits)
        
    def set_bit(self, pos: int, value: int):
        self.bits[pos] = value & 1

    def read_bit(self) -> int | None:
        if self.pos >= len(self.bits):
            return None
        bit = self.bits[self.pos]
        self.pos += 1
        return bit

    def write_bit(self, bit: int):
        self.bits.append(bit & 1)

    def write_bits(self, value: int, length: int):
        for i in reversed(range(length)):
            self.write_bit((value >> i) & 1)

    def to_bytes(self) -> bytes:
        return bytes(''.join(map(str, self.bits)), 'utf-8')
    
    def to01(self) -> str:
        return ''.join(map(str, self.bits))
