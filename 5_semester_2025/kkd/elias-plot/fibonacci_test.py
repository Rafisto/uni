# Rafał Włodarczyk 279762
from bitstream import BitStream
from fibonacci import Fibonacci

def test_fibonacci_encode():
    assert Fibonacci.encode(1).to_bytes() == b'11'
    assert Fibonacci.encode(2).to_bytes() == b'011'
    assert Fibonacci.encode(3).to_bytes() == b'0011'
    assert Fibonacci.encode(4).to_bytes() == b'1011'
    assert Fibonacci.encode(5).to_bytes() == b'00011'
    assert Fibonacci.encode(6).to_bytes() == b'10011'
    assert Fibonacci.encode(7).to_bytes() == b'01011'
    assert Fibonacci.encode(8).to_bytes() == b'000011'
    assert Fibonacci.encode(9).to_bytes() == b'100011'
    assert Fibonacci.encode(10).to_bytes() == b'010011'
    assert Fibonacci.encode(11).to_bytes() == b'001011'
    assert Fibonacci.encode(12).to_bytes() == b'101011'
    
def test_fibonacci_decode():
    assert Fibonacci.decode(BitStream('11')) == 1
    assert Fibonacci.decode(BitStream('011')) == 2
    assert Fibonacci.decode(BitStream('0011')) == 3
    assert Fibonacci.decode(BitStream('1011')) == 4
    assert Fibonacci.decode(BitStream('00011')) == 5
    assert Fibonacci.decode(BitStream('10011')) == 6
    assert Fibonacci.decode(BitStream('01011')) == 7
    assert Fibonacci.decode(BitStream('000011')) == 8
    assert Fibonacci.decode(BitStream('100011')) == 9
    assert Fibonacci.decode(BitStream('010011')) == 10
    assert Fibonacci.decode(BitStream('001011')) == 11
    assert Fibonacci.decode(BitStream('1010110000')) == 12
    assert Fibonacci.decode(BitStream('1000100001100000')) == 98