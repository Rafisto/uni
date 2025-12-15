import sys
import os
import struct


def predictor_west(matrix, i, j):
    return matrix[i][j-1] if j > 0 else 0


def predictor_north(matrix, i, j):
    return matrix[i-1][j] if i > 0 else 0


def predictor_north_west(matrix, i, j):
    return matrix[i-1][j-1] if i > 0 and j > 0 else 0


def predictor_opposite(matrix, i, j):
    if i == 0 or j == 0:
        return 0

    N = matrix[i-1][j]
    W = matrix[i][j-1]
    NW = matrix[i-1][j-1]

    return N + W - NW


def predictor_mixed_one(matrix, i, j):
    if i == 0 or j == 0:
        return 0
    N = matrix[i-1][j]
    W = matrix[i][j-1]
    NW = matrix[i-1][j-1]

    return N + (W - NW) / 2


def predictor_mixed_two(matrix, i, j):
    if i == 0 or j == 0:
        return 0
    N = matrix[i-1][j]
    W = matrix[i][j-1]
    NW = matrix[i-1][j-1]

    return W + (N - NW) / 2


def predictor_median(matrix, i, j):
    if i == 0 or j == 0:
        return 0
    N = matrix[i-1][j]
    W = matrix[i][j-1]

    return (N + W) / 2


def predictor_new(matrix, i, j):
    if i == 0 or j == 0:
        return 0
    N = matrix[i-1][j]
    W = matrix[i][j-1]
    NW = matrix[i-1][j-1]

    if NW >= max(W, N):
        return max(W, N)
    elif NW <= min(W, N):
        return min(W, N)
    else:
        return W + N - NW


def pred_modular(val):
    return (val + 256) % 256


def matrix_entropy(matrix):
    from collections import Counter
    import math

    flat = []
    r = []
    g = []
    b = []
    for row in matrix:
        for cell in row:
            if isinstance(cell, tuple):
                flat.extend(cell)
                # r.append(cell[0])
                # g.append(cell[1])
                # b.append(cell[2])
            else:
                flat.append(cell)

    if r and g and b:
        flat = r + g + b
    total = len(flat)
    freq = Counter(flat)

    entropy = 0.0
    for count in freq.values():
        p = count / total
        entropy -= p * math.log2(p)

    return entropy


def load_tga(filename):
    with open(filename, "rb") as f:
        header = f.read(18)
        (
            id_length,
            color_map_type,
            image_type,
            color_map_origin,
            color_map_length,
            color_map_depth,
            x_origin,
            y_origin,
            width,
            height,
            pixel_depth,
            image_descriptor
        ) = struct.unpack("<BBBHHBHHHHBB", header)

        if image_type != 2:
            raise ValueError(
                "Only uncompressed true-color TGA files are supported.")

        if id_length:
            f.read(id_length)

        if color_map_type:
            f.read(color_map_length * (color_map_depth // 8))

        bytes_per_pixel = pixel_depth // 8
        image_size = width * height * bytes_per_pixel
        pixel_data = f.read(image_size)

        pixels = []
        for i in range(0, len(pixel_data), bytes_per_pixel):
            if bytes_per_pixel == 3:
                b, g, r = pixel_data[i:i+3]
                pixels.append((r, g, b))
            elif bytes_per_pixel == 4:
                b, g, r, a = pixel_data[i:i+4]
                pixels.append((r, g, b, a))
            else:
                raise ValueError("Unsupported pixel depth.")

        return {
            "width": width,
            "height": height,
            "pixel_depth": pixel_depth,
            "image_descriptor": image_descriptor,
            "pixels": pixels
        }


if len(sys.argv) != 2:
    print("Usage: python predictor.py <tga_image>")
    sys.exit(1)

file = sys.argv[1]
if not os.path.isfile(file):
    print(f"File not found: {file}")
    sys.exit(1)

a = load_tga(file)
print(f"Image Size: {a["width"]}x{a["height"]}")
w = int(a["width"])
h = int(a["height"])
pixels = a["pixels"]
matrix = [pixels[i * w:(i + 1) * w] for i in range(h)]
r_matrix = [[pixels[i * w + j][0] for j in range(w)] for i in range(h)]
g_matrix = [[pixels[i * w + j][1] for j in range(w)] for i in range(h)]
b_matrix = [[pixels[i * w + j][2] for j in range(w)] for i in range(h)]

base_entropy = {
    "full": matrix_entropy(matrix),
    "red": matrix_entropy(r_matrix),
    "green": matrix_entropy(g_matrix),
    "blue": matrix_entropy(b_matrix)
}

print(f"\x1b[38;2;255;0;0mBase\x1b[0m Entropy: {base_entropy['full']}")
print(f"- red channel entropy: {base_entropy['red']}")
print(f"- green channel entropy: {base_entropy['green']}")
print(f"- blue channel entropy: {base_entropy['blue']}\n")

predictors = (
    predictor_west,
    predictor_north,
    predictor_north_west,
    predictor_opposite,
    predictor_mixed_one,
    predictor_mixed_two,
    predictor_median,
    predictor_new
)

sin_score = {
    predictor_west: 0.0,
    predictor_north: 0.0,
    predictor_north_west: 0.0,
    predictor_opposite: 0.0,
    predictor_mixed_one: 0.0,
    predictor_mixed_two: 0.0,
    predictor_median: 0.0,
    predictor_new: 0.0
}

score = {}

for c in ["full", "red", "green", "blue"]:
    score[c] = sin_score.copy()

for p in predictors:
    print(f"\x1b[38;2;255;0;0mPredictor\x1b[0m: {p.__name__}")

    # podaj entropię dla każdego predyktora
    p_matrix = [pixels[i * w:(i + 1) * w] for i in range(h)]
    for i in range(h):
        for j in range(w):
            o_r = r_matrix[i][j]
            o_g = g_matrix[i][j]
            o_b = b_matrix[i][j]

            p_r = int(p(r_matrix, i, j))
            p_g = int(p(g_matrix, i, j))
            p_b = int(p(b_matrix, i, j))

            e_r = pred_modular(o_r - p_r)
            e_g = pred_modular(o_g - p_g)
            e_b = pred_modular(o_b - p_b)

            p_matrix[i][j] = (e_r, e_g, e_b)

    entropy = matrix_entropy(p_matrix)
    print(f"Full Entropy: {entropy}")
    score["full"][p] = entropy

    # oraz dla poszczególnych składowych koloru
    for channel in range(3):
        if channel == 0:
            c_matrix = r_matrix
        elif channel == 1:
            c_matrix = g_matrix
        else:
            c_matrix = b_matrix

        p_c_matrix = [[0]*w for _ in range(h)]
        for i in range(h):
            for j in range(w):
                o_c = c_matrix[i][j]
                p_c = int(p(c_matrix, i, j))
                e_c = pred_modular(o_c - p_c)
                p_c_matrix[i][j] = e_c

        entropy_c = matrix_entropy(p_c_matrix)
        color = ['red', 'green', 'blue'][channel]
        print(f"- {color} channel entropy: {round(entropy_c,4)}")
        score[color][p] = entropy_c

print("\n\x1b[1mSummary of Entropies:\x1b[0m")
print("Lowest entropy indicates the best predictor.\n")

ansi = {
    "full": "\x1b[38;2;255;255;0mfull\x1b[0m",
    "red": "\x1b[38;2;255;0;0mred\x1b[0m",
    "green": "\x1b[38;2;0;255;0mgreen\x1b[0m",
    "blue": "\x1b[38;2;0;0;255mblue\x1b[0m"
}

for c in ["full", "red", "green", "blue"]:
    best_predictor = min(score[c], key=lambda p: score[c][p])
    print(f"(color={ansi[c]}) (name={best_predictor.__name__}) "
        f"(entropy={round(score[c][best_predictor],4)}) "
        f"(diff={round(abs(base_entropy[c]-score[c][best_predictor]),4)})")
