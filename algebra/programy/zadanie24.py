import sys
if len(sys.argv) != 2:
    print(f"Usage {sys.argv[0]} [n] - where n is a number in Zn")
    sys.exit(1)

n = int(sys.argv[1])

if n <= 2:
    print("n must be greater than 2")
    sys.exit(1)

print(f"Addition table of Z{n}, a + b (mod {n})")
print('+  ' + ' '.join([str(i) for i in range(n)]))
for i in range(n):
    print(f"{i}:", end=" ")
    for j in range(n):
        print((i+j) % n, end=" ")
    print('')

print(f"Multiplication table of Z{n} a * b (mod {n})")
print('*  ' + ' '.join([str(i) for i in range(n)]))
for i in range(n):
    print(f"{i}:", end=" ")
    for j in range(n):
        print((i*j) % n, end=" ")
    print('')