import ctypes
import os

ctypes.CDLL('libgnat.so', mode=ctypes.RTLD_GLOBAL)

C_LIB_SO = "../1_libjpp_c/libjpp.so"
ADA_LIB_SO = "../2_libjpp_ada/libjpp.so"
RUST_LIB_SO = "../3_libjpp_rust/target/release/libjpp.so"

lib_paths = [C_LIB_SO, ADA_LIB_SO, RUST_LIB_SO]

for path in lib_paths:
    lib = ctypes.cdll.LoadLibrary(os.path.relpath(path))
    print(f"Testing {path}...")
    print(lib.gcd(48, 18))
    lib.diophantine(48, 18, 6)
