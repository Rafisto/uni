# python extended euclidean algorithm
import sys

if len(sys.argv) != 3:
    print(f"Diophantine equation solver: [a]y + [b]y = GCD([a],[b])")
    print(f"Usage: {sys.argv[0]} [a] [b]")
    sys.exit(0)

a, b = int(sys.argv[1]), int(sys.argv[2])
x, y, prev_x, prev_y = 0, 1, 1, 0

while b != 0:
    quotient = a // b
    a, b = b, a % b
    x, prev_x = prev_x - quotient * x, x
    y, prev_y = prev_y - quotient * y, y

print(f"[{sys.argv[1]}]x + [{sys.argv[2]}]y = GCD({sys.argv[1]},{sys.argv[2]}) = {a}")
print(f"x = {prev_x}, y = {prev_y}")