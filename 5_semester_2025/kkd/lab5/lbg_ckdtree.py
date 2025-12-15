import numpy as np
from scipy.spatial import cKDTree

def approx_to_uint8(color):
    return np.array([max(0, min(255, int(round(c)))) for c in color])

def lloyd_kdtree(vectors, codebook):
    tree = cKDTree(codebook)  
    _, indices = tree.query(vectors, k=1)

    clusters = {i: [] for i in range(len(codebook))}
    for idx, v in zip(indices, vectors):
        clusters[idx].append(v)

    for i in range(len(codebook)):
        if clusters[i]:
            codebook[i] = approx_to_uint8(np.mean(clusters[i], axis=0))

    return codebook

def linde_buzo_gray(vectors, old_codebook, i, better=False):
    new_codebook = []
    eps = 0.01
    for color in old_codebook:
        if not better:
            new_codebook.append(np.array([c + 1 for c in color]))
            new_codebook.append(np.array([c - 1 for c in color]))
        else:
            new_codebook.append(np.array([color[0] * (1-eps), color[1], color[2]]))
            new_codebook.append(np.array([color[0] * (1+eps), color[1], color[2]]))
            new_codebook.append(np.array([color[0], color[1] * (1-eps), color[2]]))
            new_codebook.append(np.array([color[0], color[1] * (1+eps), color[2]]))
            new_codebook.append(np.array([color[0], color[1], color[2] * (1-eps)]))
            new_codebook.append(np.array([color[0], color[1], color[2] * (1+eps)]))


    return lloyd_kdtree(vectors, new_codebook)
