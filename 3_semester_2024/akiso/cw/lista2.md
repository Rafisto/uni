- [Zadanie 1](#zadanie-1)
    - [Krok 1: Zamiana liczby 120.5 z systemu dziesiętnego na inne podstawy](#krok-1-zamiana-liczby-1205-z-systemu-dziesiętnego-na-inne-podstawy)
      - [1.1. Zamiana części całkowitej (120)](#11-zamiana-części-całkowitej-120)
      - [1.2. Zamiana części ułamkowej (0.5)](#12-zamiana-części-ułamkowej-05)
    - [Krok 2: Zamiana liczby 8.2 z systemu dziesiętnego na inne podstawy](#krok-2-zamiana-liczby-82-z-systemu-dziesiętnego-na-inne-podstawy)
      - [2.1. Zamiana części całkowitej (8)](#21-zamiana-części-całkowitej-8)
      - [2.2. Zamiana części ułamkowej (0.2)](#22-zamiana-części-ułamkowej-02)
    - [Krok 3: Dodawanie liczb](#krok-3-dodawanie-liczb)
- [Zadanie 2](#zadanie-2)
- [Zadanie 3](#zadanie-3)
- [Zadanie 4](#zadanie-4)
- [Zadanie 5](#zadanie-5)
  - [Zadanie 5.1](#zadanie-51)
  - [Zadanie 5.2](#zadanie-52)
  - [Zadanie 5.3](#zadanie-53)
- [Zadanie 6 - BCD](#zadanie-6---bcd)
- [Zadanie 7 - Unicode](#zadanie-7---unicode)
- [Zadanie 8 - Gray Codes](#zadanie-8---gray-codes)
- [Zadanie 9 - Fast inverse square root](#zadanie-9---fast-inverse-square-root)

# Zadanie 1

Aby zamienić liczby dziesiętne \(120.5\) i \(8.2\) na liczby w różnych systemach liczbowych (o podstawach 3, 4, 7, 8 i 16), postępujemy w kilku krokach:

### Krok 1: Zamiana liczby 120.5 z systemu dziesiętnego na inne podstawy

#### 1.1. Zamiana części całkowitej (120)

W tym celu będziemy dzielić liczbę całkowitą przez nową podstawę, zapisując reszty, aż do uzyskania wyniku 0.

**Podstawa 3:**
1. \( 120 \div 3 = 40\), reszta 0
2. \( 40 \div 3 = 13\), reszta 1
3. \( 13 \div 3 = 4\), reszta 1
4. \( 4 \div 3 = 1\), reszta 1
5. \( 1 \div 3 = 0\), reszta 1

Zatem \(120_{10} = 11110_3\).

**Podstawa 4:**
1. \( 120 \div 4 = 30\), reszta 0
2. \( 30 \div 4 = 7\), reszta 2
3. \( 7 \div 4 = 1\), reszta 3
4. \( 1 \div 4 = 0\), reszta 1

Zatem \(120_{10} = 1320_4\).

**Podstawa 7:**
1. \( 120 \div 7 = 17\), reszta 1
2. \( 17 \div 7 = 2\), reszta 3
3. \( 2 \div 7 = 0\), reszta 2

Zatem \(120_{10} = 231_7\).

**Podstawa 8:**
1. \( 120 \div 8 = 15\), reszta 0
2. \( 15 \div 8 = 1\), reszta 7
3. \( 1 \div 8 = 0\), reszta 1

Zatem \(120_{10} = 170_8\).

**Podstawa 16:**
1. \( 120 \div 16 = 7\), reszta 8
2. \( 7 \div 16 = 0\), reszta 7

Zatem \(120_{10} = 78_{16}\).

#### 1.2. Zamiana części ułamkowej (0.5)

Aby zamienić część ułamkową, mnożymy ją przez nową podstawę, zapisując liczby całkowite po przecinku.

**Podstawa 3:**
1. \( 0.5 \times 3 = 1.5\), zapisujemy 1
2. \( 0.5 \times 3 = 1.5\), zapisujemy 1 (ten proces będzie powtarzalny)

Zatem \(0.5_{10} = 0.111111..._3\).

**Podstawa 4:**
1. \( 0.5 \times 4 = 2.0\), zapisujemy 2

Zatem \(0.5_{10} = 0.2_4\).

**Podstawa 7:**
1. \( 0.5 \times 7 = 3.5\), zapisujemy 3
2. \( 0.5 \times 7 = 3.5\), zapisujemy 3 (proces powtarzalny)

Zatem \(0.5_{10} = 0.3333..._7\).

**Podstawa 8:**
1. \( 0.5 \times 8 = 4.0\), zapisujemy 4

Zatem \(0.5_{10} = 0.4_8\).

**Podstawa 16:**
1. \( 0.5 \times 16 = 8.0\), zapisujemy 8

Zatem \(0.5_{10} = 0.8_{16}\).

### Krok 2: Zamiana liczby 8.2 z systemu dziesiętnego na inne podstawy

#### 2.1. Zamiana części całkowitej (8)

**Podstawa 3:**
1. \( 8 \div 3 = 2\), reszta 2
2. \( 2 \div 3 = 0\), reszta 2

Zatem \(8_{10} = 22_3\).

**Podstawa 4:**
1. \( 8 \div 4 = 2\), reszta 0
2. \( 2 \div 4 = 0\), reszta 2

Zatem \(8_{10} = 20_4\).

**Podstawa 7:**
1. \( 8 \div 7 = 1\), reszta 1
2. \( 1 \div 7 = 0\), reszta 1

Zatem \(8_{10} = 11_7\).

**Podstawa 8:**
1. \( 8 \div 8 = 1\), reszta 0
2. \( 1 \div 8 = 0\), reszta 1

Zatem \(8_{10} = 10_8\).

**Podstawa 16:**
1. \( 8 \div 16 = 0\), reszta 8

Zatem \(8_{10} = 8_{16}\).

#### 2.2. Zamiana części ułamkowej (0.2)

**Podstawa 3:**
1. \( 0.2 \times 3 = 0.6\), zapisujemy 0
2. \( 0.6 \times 3 = 1.8\), zapisujemy 1
3. \( 0.8 \times 3 = 2.4\), zapisujemy 2
4. \( 0.4 \times 3 = 1.2\), zapisujemy 1

Zatem \(0.2_{10} = 0.0121_3\).

**Podstawa 4:**
1. \( 0.2 \times 4 = 0.8\), zapisujemy 0
2. \( 0.8 \times 4 = 3.2\), zapisujemy 3
3. \( 0.2 \times 4 = 0.8\), zapisujemy 0 (proces powtarzalny)

Zatem \(0.2_{10} = 0.0303..._4\).

**Podstawa 7:**
1. \( 0.2 \times 7 = 1.4\), zapisujemy 1
2. \( 0.4 \times 7 = 2.8\), zapisujemy 2
3. \( 0.8 \times 7 = 5.6\), zapisujemy 5
4. \( 0.6 \times 7 = 4.2\), zapisujemy 4

Zatem \(0.2_{10} = 0.1254_7\).

**Podstawa 8:**
1. \( 0.2 \times 8 = 1.6\), zapisujemy 1
2. \( 0.6 \times 8 = 4.8\), zapisujemy 4

Zatem \(0.2_{10} = 0.14_8\).

**Podstawa 16:**
1. \( 0.2 \times 16 = 3.2\), zapisujemy 3
2. \( 0.2 \times 16 = 3.2\), zapisujemy 3 (proces powtarzalny)

Zatem \(0.2_{10} = 0.33_{16}\).

### Krok 3: Dodawanie liczb

Teraz możemy dodać obie liczby w wybranych systemach liczbowych.

**Podstawa 3:**
\(120.5_{10} \approx 11110.111_3 + 22.0121_3 = 11132.1001_3\)

**Podstawa 4:**
\(120.5_{10} = 1320.2_4 + 20.03_4 = 1340.23_4\)

**Podstawa 7:**
\(120.5_{10} = 231.333_7 + 11.1254_7 = 243.501_7\)

**Podstawa 8:**
\(120.5_{10} = 170.4_8 + 10.14_8 = 200.54_8\)

**Podstawa 16:**
\(120.5_{10} = 78.8_{16} + 8.33_{16} = 80.B3_{16}\)

Ostateczne wyniki w różnych podstawach są przybliżeniami, ponieważ części ułamkowe są okresowe w niektórych przypadkach.

# Zadanie 2

Decimal to binary:

10.0625 = $1010.0001_(2)$
104 - $1101000_(2)$
2014 - $11111011110_(2)$
673.23 = ~$0010 1010 0001.0011 1010 1110 0001 0100 1000_(2)$

# Zadanie 3

225.225 = $22100,0(2000)_(3)$
225.225 = $441.(1401)\_(7)

# Zadanie 4

Base 7:

- Max - 5 digits, one after comma: $6666.6$
- Min - -||- : $1000.0$

Base 3:

- Max - 7 digits, 2 comma, one sign: $+22222.22$
- Min - $-22222.22$

# Zadanie 5

Check whether exists such p that:

## Zadanie 5.1

$(BEE)_p = (2699)_10$

$(BEE)_p = p^2 + 14p + 14 = 2699$
$p^2 + 14p - 2685 = 0$

Neither $p_1$ nor $p_2$ are integers.

## Zadanie 5.2

$(365)_p = (194)_10$
$(365)_p = 3p^2 + 6p + 5 = 194$
$3p^2 + 6p - 189 = 0$
$p_1 = 7$
$p_2 = -9$

Answer: $p = 7$ because for $p = -9$ the number is negative.

## Zadanie 5.3

$((34)_p + (24)_p) * (21)_p = (1480)_p$
$(3*p+4 + 2*p+4) * (2*p+1) = 1480$
$10p^2 + 21p + 8 = p^3 + 4p^2 + 8p$
$ p^3 - 6p^2 - 13p - 8 = 0$
$p ~= 7.8$

Baza $4$ oraz baza $8$ nie może być poniewaz mamy $8$ z zapisie $1480$, wobec tego nie ma takiej podstawy `p` która spełnia równianie.

# Zadanie 6 - BCD

- Łatwo się czyta - 4 bity rzutem oka można ogarnąć
- Nieoptymalny (10 znaków, a 16 możliwych do zakodowania)

127 - `0001 0010 0111`
1616 - `0001 0110 0110 0110`
2017 - `0010 0000 0001 0111`

> (*) How to do arithmetic operations in BCD
> (*) Construct: Binary to channel encoder.

# Zadanie 7 - Unicode

[UTF-8 Character List](https://www.fileformat.info/info/charset/UTF-8/list.htm)

Encoding schema (any length):
1. **0**xxxxxxx <- char (7)
2. **110**xxxxx**10**xxxxxx (11)
3. **1110** ... **10 ... **10**
4. **11110** ... **10** ... **10** ... **10** ...

Encoding a single character:

`ę` = U+$0119_{16}$ = $0000 0001 0001 1001_2$ - interesting bits `100011001` - there are 9 of them
Choose encoding schema - 2:

`1100 0100 1001 1001` = `c499`
**110**00100**10**011001$

UTF-8 is backwards compatible with ASCII.

`pięść` = `0x70 0x69 0xc4 0x99 0xc5 0x9b 0xc4 0x87`

- `0x70` (ASCII `p`)
- `0x69` (ASCII `i`)
- `0xc4 0x99` (UTF-8 sequence for the letter `ę`)
- `0xc5 0x9b` (UTF-8 sequence for the letter `ś`)
- `0xc4 0x87` (UTF-8 sequence for the letter `ć`)

When this is decoded, the output string is `pięść`, which has $5$ letters.
The special characters `ę`, `ś,` and `ć` each require two bytes in `UTF-8` but represent single letters.

`0xc4` page and `0xc5` page. The `0xc4` byte is used to represent many accented Latin characters.

# Zadanie 8 - Gray Codes

Gray code construction is a recursive process. It ensures that successive numbers differ by only one bit.

2 bit gray codes: $00, 01, 11, 10$
3 bit gray codes: $000, 001, 011, 010, 110, 111, 101, 100$
4 bit gray codes: $0000, 0001, 0011, 0010, 0110, 0111, 0101, 0100, 1100, 1101, 1111, 1110, 1010, 1011, 1001, 1000$

XOR-ujemy z ją samą przesuniętą o jeden.

- $(7)_10 = 0111$
- $(8)_10 = 1000$

```bash
0 - 000
1 - 001 -> 001 (001 xor 000 = 001)
2 - 010 -> 011 (010 xor 001 = 011)
3 - 011 -> 010
4 - 100 -> 110
```

- Może być na kolokwium unicode + gray codes

# Zadanie 9 - Fast inverse square root

```c
float InvSqrt(float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f-xhalf*x*x);
    return x;
}
```

This is drastically difficult to understand.
