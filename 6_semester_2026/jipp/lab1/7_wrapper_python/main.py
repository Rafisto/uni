import ctypes
import libjpp
import test

C_LIB_SO = "../1_libjpp_c/libjpp.so"
ADA_LIB_SO = "../2_libjpp_ada/libjpp.so"
RUST_LIB_SO = "../3_libjpp_rust/target/release/libjpp.so"

lib_paths = (C_LIB_SO, ADA_LIB_SO, RUST_LIB_SO)

ctypes.CDLL("libgnat.so", mode=ctypes.RTLD_GLOBAL)

for lib_path in lib_paths:
    lib = libjpp.load_libjpp_dynamic(lib_path)

    print(lib_path)
    test.test_gcd(lib)
    test.test_first_prime_div(lib)
    test.test_phi(lib)
    test.test_diophantine(lib)
