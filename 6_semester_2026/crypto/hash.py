import hashlib
import numpy as np
import matplotlib.pyplot as plt

num_samples = 20000

uniform_input = np.random.randint(0, 1000000, num_samples)
normal_input = np.random.normal(500000, 100000, num_samples).astype(int)
exp_input = np.random.exponential(scale=100000, size=num_samples).astype(int)
beta_input = np.random.beta(a=2, b=5, size=num_samples) * 1000000

md5 = lambda x : hashlib.md5(str(x).encode()).hexdigest()
sha1 = lambda x : hashlib.sha1(str(x).encode()).hexdigest()
sha256 = lambda x : hashlib.sha256(str(x).encode()).hexdigest()
pkdf2 = lambda x : hashlib.pbkdf2_hmac('sha256', str(x).encode(), b'salt', 100000).hex()
non_hash = lambda x : str(x).encode().hex()[:64]

# funcs = [md5, sha1, sha256, non_hash]
# funcs = [pkdf2]
funcs = [non_hash]

for i, func in enumerate(funcs):
    uniform_hashes = [func(x) for x in uniform_input]
    normal_hashes = [func(x) for x in normal_input]
    exp_hashes = [func(x) for x in exp_input]
    beta_hashes = [func(x) for x in beta_input]

    plt.figure(figsize=(12, 10))
    plt.subplot(2, 2, 1)
    plt.hist(uniform_input, bins=64, alpha=0.7, label='Uniform', color='blue')
    plt.hist(normal_input, bins=64, alpha=0.7, label='Normal', color='red')
    plt.hist(exp_input, bins=64, alpha=0.7, label='Exponential', color='green')
    plt.hist(beta_input, bins=64, alpha=0.7, label='Beta', color='orange')
    plt.xlim(0,1000000)
    plt.xlabel('Input Values')
    plt.ylabel('Frequency')
    plt.title('Distribution of Inputs')
    plt.legend()

    fb = lambda h : int(h[:2], 16) & 0xFF

    uniform_hashes_first_byte = [fb(h) for h in uniform_hashes]
    normal_hashes_first_byte = [fb(h) for h in normal_hashes]
    exp_hashes_first_byte = [fb(h) for h in exp_hashes]
    beta_hashes_first_byte = [fb(h) for h in beta_hashes]

    plt.subplot(2, 2, 2)
    plt.hist(uniform_hashes_first_byte, bins=64, alpha=0.5, label='Uniform Input', color='blue', histtype='stepfilled')
    plt.hist(normal_hashes_first_byte, bins=64, alpha=0.4, label='Normal Input', color='red', histtype='stepfilled')
    plt.hist(exp_hashes_first_byte, bins=64, alpha=0.3, label='Exponential Input', color='green', histtype='stepfilled')
    plt.hist(beta_hashes_first_byte, bins=64, alpha=0.2, label='Beta Input', color='orange', histtype='stepfilled')
    plt.xlabel('Hash Values')
    plt.ylabel('Count')
    plt.title('First Byte')
    plt.legend()

    plt.subplot(2, 2, 3)

    binc = lambda h : bin(int(h, 16)).count('1')

    uniform_ones = [binc(h) for h in uniform_hashes]
    normal_ones = [binc(h) for h in normal_hashes]
    exp_ones = [binc(h) for h in exp_hashes]
    beta_ones = [binc(h) for h in beta_hashes]

    plt.hist(uniform_ones, bins=64, alpha=0.5, label='Uniform Input', color='blue', histtype='stepfilled')
    plt.hist(normal_ones, bins=64, alpha=0.4, label='Normal Input', color='red', histtype='stepfilled')
    plt.hist(exp_ones, bins=64, alpha=0.3, label='Exponential Input', color='green', histtype='stepfilled')
    plt.hist(beta_ones, bins=64, alpha=0.2, label='Beta Input', color='orange', histtype='stepfilled')
    plt.xlabel('Number of 1s in Binary')
    plt.ylabel('Count')
    plt.title('Count of 1s in Hash')
    plt.legend()

    plt.subplot(2, 2, 4)

    ascii_sum = lambda h: sum(ord(c) for c in h)

    uniform_ascii = [ascii_sum(h) for h in uniform_hashes]
    normal_ascii = [ascii_sum(h) for h in normal_hashes]
    exp_ascii = [ascii_sum(h) for h in exp_hashes]
    beta_ascii = [ascii_sum(h) for h in beta_hashes]

    plt.hist(uniform_ascii, bins=64, alpha=0.5, label='Uniform Input', color='blue', histtype='stepfilled')
    plt.hist(normal_ascii, bins=64, alpha=0.4, label='Normal Input', color='red', histtype='stepfilled')
    plt.hist(exp_ascii, bins=64, alpha=0.3, label='Exponential Input', color='green', histtype='stepfilled')
    plt.hist(beta_ascii, bins=64, alpha=0.2, label='Beta Input', color='orange', histtype='stepfilled')
    plt.xlabel('Sum of ASCII Values')
    plt.ylabel('Count')
    plt.title('Sum of ASCII Values in Hash')
    plt.legend()

    plt.tight_layout()
    plt.savefig(f'{i}_analysis.png')
