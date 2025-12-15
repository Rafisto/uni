# Rafał Włodarczyk 279762
import csv
from typing import Dict, List

import numpy as np
import matplotlib.pyplot as plt

from elias import Elias
from fibonacci import Fibonacci

# RANGE=1_000
RANGE=1_000_000
x = range(RANGE+1)[1:]

lengths: Dict[str, List[int]] = {
    'binary': [],
    'dbinary': [],
    'gamma': [],
    'delta': [],
    'omega': [],
    'fibonacci': []
}

for r in x:
    print(f'Encoding number: {r}', end='\r')
    binary = bin(r)[2:]
    gamma = Elias.gamma_encode(r)
    delta = Elias.delta_encode(r)
    omega = Elias.omega_encode(r)
    fibonacci = Fibonacci.encode(r)

    lengths['binary'].append(len(binary))
    lengths['dbinary'].append(2*len(binary))
    lengths['gamma'].append(gamma.length())
    lengths['delta'].append(delta.length())
    lengths['omega'].append(omega.length())
    lengths['fibonacci'].append(fibonacci.length())

# plt.step(x, lengths['dbinary'], label="Kodowanie Naiwne", color='navy', lw=3)
plt.step(x, lengths['binary'], label='Kodowanie Binarne', color='blue', lw=2)
plt.step(x, lengths['omega'], label='Kodowanie Omega', color='red', lw=2)
plt.step(x, lengths['gamma'], label='Kodowanie Gamma', color='orange', linestyle='--', lw=2)
plt.step(x, lengths['delta'], label='Kodowanie Delta', color='green', linestyle='-.', lw=2)
plt.xlabel('Liczba naturalna n')
plt.ylabel('Długość kodu w bitach')
plt.title('Porównanie kodowań γ, δ i ω Eliasa z kodowaniem binarnym')
plt.legend()

plt.yticks(np.arange(0, max(lengths['omega'])+1, 5))

plt.grid(True)
plt.savefig(f'elias_encoding_{RANGE}.png', dpi=300)

plt.xscale('log')
plt.savefig(f'elias_encoding_log_{RANGE}.png', dpi=300)
plt.xscale('linear')

plt.step(x, lengths['fibonacci'], label='Kodowanie Fibonacciego', color='purple', linestyle=':', lw=2)
plt.legend()
plt.title('Porównanie Fibonacciego, Eliasa i kodowania binarnego')
plt.savefig(f'all_encodings_{RANGE}.png', dpi=300)

plt.xscale('log')
plt.savefig(f'all_encodings_log_{RANGE}.png', dpi=300)
