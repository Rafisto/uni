import ctypes
import os
from typing import Type

class DiophantineResult64(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_uint64),
        ("y", ctypes.c_uint64),
        ("err", ctypes.c_bool),
    ]

    def __repr__(self) -> str:
        return f"x={self.x}, y={self.y}, err={self.err}"

class LibJPP:
    """A type-safe wrapper for the libjpp shared library."""
    def __init__(self, lib: ctypes.CDLL):
        self._lib = lib
        
        self._lib.gcd.argtypes = [ctypes.c_uint64, ctypes.c_uint64]
        self._lib.gcd.restype = ctypes.c_uint64

        self._lib.first_prime_div.argtypes = [ctypes.c_uint64]
        self._lib.first_prime_div.restype = ctypes.c_uint64

        self._lib.phi.argtypes = [ctypes.c_uint64]
        self._lib.phi.restype = ctypes.c_uint64

        self._lib.diophantine.argtypes = [ctypes.c_uint64, ctypes.c_uint64, ctypes.c_uint64]
        self._lib.diophantine.restype = DiophantineResult64

    def gcd(self, x: int, y: int) -> int:
        return self._lib.gcd(x, y)

    def first_prime_div(self, n: int) -> int:
        return self._lib.first_prime_div(n)

    def phi(self, n: int) -> int:
        return self._lib.phi(n)

    def diophantine(self, a: int, b: int, c: int) -> DiophantineResult64:
        return self._lib.diophantine(a, b, c)

def load_libjpp_dynamic(path: str) -> LibJPP:
    real_path = os.path.abspath(path)
    cdll_obj = ctypes.CDLL(real_path)
    return LibJPP(cdll_obj)