# python extended euclidean algorithm
import sys

if len(sys.argv) != 3:
    print(f"Usage {sys.argv[0]} [a]x + b[y] = NWD(a,b)")
    sys.exit(0)

a, b = int(sys.argv[1]), int(sys.argv[2])
x1, x2 = 0, 1
y1, y2 = 1, 0

if a < 0 or b < 0:
    print("a and b must be positive")
    sys.exit(1)

while b > 0:
    q = a // b
    r = a % b 

    x = x1 - q * x2
    y = y1 - q * y2

    x2, x1 = x1, x
    y2, y1 = y1, y
    a, b = b, r

print(f"{sys.argv[1]}x + {sys.argv[2]}y = NWD({sys.argv[1]},{sys.argv[2]})={a}")
print(f"Result: x={x} y={y}")

