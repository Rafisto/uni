## Huffman Coding Information Bounds

$H(S) \leq I_H(S) < H(S) + 1$>
$H(s) \leq \frac{I_H(S^n)} < H(S) + \frac{1}{n}$

## Tunstall Coding

All code words have the same length, however one code can mean multiple characters from the input text.
Input alphabet $a_1,a_2,\dots, a_n$ with probabilities: $p_1,p_2,\dots, p_n$.

## Mean code bit-length

$$
\sum_{i=1}^{2^n-1} P(e_i) \frac{n}{|e_i|}
$$

## Arithmetic Coding

We assign a number from range $[0,1)$ to each text.

Text code is defined by:
- its length $n$
- pointer $z\in\mathbb{R}$

## Arithmetic Coding Limitations

We can only write $z$ using a limited number of bits.

$$
m(x) = \lceil \log \frac{1}{P(X)} \rceil + 1
$$

guarantees coding is unambiguous.


- ustalam równopodobne prawdopodobieństwa
- co 256 symboli zmieniamy rachunek prawdopodobieństwa
- zmieniam przedział po jakimś etapie - mianownik jak najbardziej wyrażalny w systemie binarnym.