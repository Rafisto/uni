# Rafał Włodarczyk 279762
import pytest
from bitstream import BitStream
from elias import Elias


def test_gamma_encode():
    enc = Elias.gamma_encode(137)
    # 7 zeros + 8 bits for 137, total 15 bits
    assert len(enc.to_bytes()) == 15
    assert enc.to_bytes() == b'000000010001001'

    enc = Elias.gamma_encode(1)
    assert len(enc.to_bytes()) == 1
    assert enc.to_bytes() == b'1'

    try:
        enc = Elias.gamma_encode(0)
        assert False, "cannot encode <=0"
    except ValueError:
        pass


def test_gamma_decode():
    bs = BitStream('000000010001001')
    assert Elias.gamma_decode(bs) == 137

    bs = BitStream('1')
    assert Elias.gamma_decode(bs) == 1


def test_delta_encode():
    enc = Elias.delta_encode(137)
    assert (enc.to_bytes() == b'00010000001001')

    enc = Elias.delta_encode(1)
    assert (enc.to_bytes() == b'1')


def test_delta_decode():
    bs = BitStream('00010000001001')
    assert Elias.delta_decode(bs) == 137

    bs = BitStream('1')
    assert Elias.delta_decode(bs) == 1


def test_omega_encode():
    enc = Elias.omega_encode(137)
    assert (enc.to_bytes() == b'10111100010010')


def test_omega_decode():
    bs = BitStream('10111100010010')
    assert Elias.omega_decode(bs) == 137


if __name__ == "__main__":
    pytest.main()
