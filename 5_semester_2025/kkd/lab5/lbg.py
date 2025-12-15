import numpy as np
import multiprocessing as mp


def approx_to_uint8(color):
    return np.array([max(0, min(255, int(round(c)))) for c in color])


def manhattan(v1, v2): return sum(abs(a - b) for a, b in zip(v1, v2))


def find_closest_cluster(v, codebook):
    closest_distance_index = np.argmin([manhattan(v, c) for c in codebook])
    return (closest_distance_index, v)


# Linde - Buzo - Gray algorithm for vector quantization
# https://en.wikipedia.org/wiki/Linde%E2%80%93Buzo%E2%80%93Gray_algorithm

def lloyd(vectors, codebook):
    num_processes = mp.cpu_count()
    with mp.Pool(num_processes) as pool:
        results = pool.starmap(find_closest_cluster, [
                               (v, codebook) for v in vectors])

    clusters = {i: [] for i in range(len(codebook))}
    for closest_index, v in results:
        clusters[closest_index].append(v)

    for i in range(len(codebook)):
        if clusters[i]:
            codebook[i] = approx_to_uint8(np.mean(clusters[i], axis=0))

    return codebook


def linde_buzo_gray(vectors, old_codebook, i, better=False):
    new_codebook = []
    for color in old_codebook:
        new_codebook.append(np.array([c * (0.90) for c in color]))
        new_codebook.append(np.array([c * (1.10) for c in color]))

    return lloyd(vectors, new_codebook)
