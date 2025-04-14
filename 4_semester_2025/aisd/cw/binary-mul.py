import math


def multiply(x: str, y: str, depth=0) -> str:
    indent = "│   " * depth  # Indentation for tree structure
    print(f"{indent}multiply('{x}', '{y}')")

    def leftmost(bits, num):
        return num[:bits] if bits > 0 else '0'

    def rightmost(bits, num):
        return num[-bits:] if bits > 0 else '0'

    x = int(x, 2)
    y = int(y, 2)

    if x == 0 or y == 0:
        print(f"{indent}├── Result: 0")
        return "0"

    if x == 1:
        print(f"{indent}├── Result: {bin(y)[2:]}")
        return bin(y)[2:]
    if y == 1:
        print(f"{indent}├── Result: {bin(x)[2:]}")
        return bin(x)[2:]

    n = max(x.bit_length(), y.bit_length())

    n_ceil = math.ceil(n / 2)
    n_floor = math.floor(n / 2)

    x_bin = bin(x)[2:].zfill(n)
    y_bin = bin(y)[2:].zfill(n)

    x_L = int(leftmost(n_ceil, x_bin), 2)
    x_R = int(rightmost(n_floor, x_bin), 2)
    y_L = int(leftmost(n_ceil, y_bin), 2)
    y_R = int(rightmost(n_floor, y_bin), 2)

    print(f"{indent}├── p1: multiply('{bin(x_L)[2:]}', '{bin(y_L)[2:]}')  # Leftmost parts")
    p1 = multiply(bin(x_L)[2:], bin(y_L)[2:], depth + 1)

    print(f"{indent}├── p2: multiply('{bin(x_R)[2:]}', '{bin(y_R)[2:]}')  # Rightmost parts")
    p2 = multiply(bin(x_R)[2:], bin(y_R)[2:], depth + 1)

    print(f"{indent}├── p3: multiply('{bin(x_L + x_R)[2:]}', '{bin(y_L + y_R)[2:]}')  # Sum of left and right parts")
    p3 = multiply(bin(x_L + x_R)[2:], bin(y_L + y_R)[2:], depth + 1)

    p1 = int(p1, 2)
    p2 = int(p2, 2)
    p3 = int(p3, 2)

    result = (p1 << (2 * n_floor)) + ((p3 - p1 - p2) << n_floor) + p2
    print(f"{indent}└── Result: {bin(result)[2:]}")
    return bin(result)[2:]


if __name__ == '__main__':
    x = '11011'
    y = '01010'
    print("Binary Multiplication Trace:")
    print(multiply(x, y))
