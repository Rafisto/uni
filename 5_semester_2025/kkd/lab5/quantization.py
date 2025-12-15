import os
import sys
import time

import numpy as np
from image import Image
from lbg_ckdtree import linde_buzo_gray, approx_to_uint8
from scipy.spatial import cKDTree


if len(sys.argv) < 4:
    print("Usage: python quantization.py <input> <output> <bitcount> [-p] [-b]")
    sys.exit(1)

detail = False
if '-p' in sys.argv:
    detail = True

better = False
if '-b' in sys.argv:
    better = True

input_file = sys.argv[1]
if not os.path.isfile(input_file):
    print(f"File not found: {input_file}")
    sys.exit(1)

output_file = sys.argv[2]
if os.path.isfile(output_file):
    print(f"Warning, output file already exists: {output_file}")

try:
    bitcount = int(sys.argv[3])
    if bitcount < 0 or bitcount > 24:
        print("Color count must be between 0 and 24.")
        sys.exit(1)
except ValueError:
    print("Color count must be an integer.")

def pretty_print_codebook(codebook):
    for i, (r,g,b) in enumerate(codebook):
        print(f"\x1b[38;2;{r};{g};{b}m█\x1b[0m", end='')
    print('\x1b[0m')

img = Image(input_file)
pixels = img.get_pixels()

raw_pixels = np.array(img.pixels, dtype=np.uint8)
reshaped_pixels = raw_pixels.reshape(-1, raw_pixels.shape[-1] if raw_pixels.ndim > 1 else 4)
image_vectors = reshaped_pixels[:, :3]

start_time = time.time()

codebook = np.array(approx_to_uint8(np.array(image_vectors).mean(axis=0).tolist())).reshape(1, 3)
for i in range(bitcount):
    if detail: print(f"LBG {str(i).zfill(int(np.log(bitcount)))}/{bitcount}:", end = " ")
    if detail: pretty_print_codebook(codebook)
    codebook = linde_buzo_gray(image_vectors, codebook, i, better)
print(f"Resulting codebook {len(codebook)} colors:")
if detail: pretty_print_codebook(codebook)

end_time = time.time()

print(f"LBG completed in {end_time - start_time:.2f} seconds.")

start_time = time.time()

tree = cKDTree(codebook)
_, indices = tree.query(image_vectors, k=1)
quantized_pixels = [codebook[idx] for idx in indices]

end_time = time.time()
print(f"Quantization completed in {end_time - start_time:.2f} seconds.")

quantized_pixels = np.array(
    quantized_pixels, dtype=np.uint8).flatten().tolist()
original_pixels = np.array(image_vectors, dtype=np.uint8).flatten().tolist()

mse = np.mean((np.array(original_pixels) - np.array(quantized_pixels))**2)
snr = 10 * np.log10(np.mean(np.array(original_pixels)**2) / mse)

print(f"MSE: {mse}")
print(f"SNR: {snr} dB")

img.set_pixels(quantized_pixels)
img.save(output_file)
