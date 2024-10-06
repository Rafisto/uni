permutation = [2, 3, 9, 1, 5, 4, 8, 7, 6]

def transposer(p):
    steps, size = [], len(p)
    vec = [0] * size
    while list(sorted(p)) != p:
        for i in range(size):
            for j in range(i, size):
                if i == j:
                    continue
                if p[i] > p[j]:
                    step = f"({i+1} {j+1})"
                    steps.append(step)
                    vec[j] += 1
                    p[i], p[j] = p[j], p[i]
    return steps[::-1], vec


def vec_to_permutation(v):
    size = len(v)
    perm = [(i+1) for i in range(size)]
    while [0]*size != v:
        c = max(v)
        print(c)
        for i in range(size):
            if v[i] == c:
                print(f"{i} {perm}")
                perm[i-1], perm[i] = perm[i], perm[i-1]
                v[i] -= 1
            
    return perm
                
    
print(f"Initial P=({' '.join([str(p) for p in permutation])})")              
S, v = transposer(permutation)
print(f"Steps:\n{'*'.join(S)}")    
print(f"Transposition vector:\nv={v}")
P = vec_to_permutation(v)
print(f"Reconstructed permutation:\nP=({' '.join([str(p) for p in P])})")