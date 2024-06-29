# python euclidean algorithm
import sys

if len(sys.argv) != 3:
    print(f"Usage {sys.argv[0]} a b")
    print(f"Result: NWD(a,b)")
    sys.exit(0)

a = int(sys.argv[1])
b = int(sys.argv[2])

if a < 0 or b < 0:
    print("a and b must be positive")
    sys.exit(1)

while a != b:
    if a > b:
        a -= b
    else:
        b -= a

print(f"NWD({sys.argv[1]}, {sys.argv[2]}) = {a}")
