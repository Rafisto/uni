1. Podstawy:

- Zrozumienie mintermów i maxtermów:
    - Mintermy (m): kiedy funkcja logiczna przyjmuje wartość 1.
    - Maxtermy (M): kiedy funkcja logiczna przyjmuje wartość 0.
    - Konwersja między Σm (suma mintermów) a ΠM (iloczyn maxtermów).

- Tablica prawdy:
    - Tworzenie tablicy prawdy dla funkcji logicznej na podstawie liczby zmiennych.
    - Mapowanie mintermów i maxtermów na indeksy.

- Postacie funkcji:
    - Postać kanoniczna sumy iloczynów (SOP, ang. Sum of Products).
    - Postać kanoniczna iloczynu sum (POS, ang. Product of Sums).

2. Siatka Karnaugha (Karnaugh Map):

- Budowa siatki Karnaugha:
    - Tworzenie siatki dla 2, 3, 4 zmiennych.
    - Uporządkowanie pól według kodu Graya.

- Grupowanie pól:
    - Tworzenie grup 11 (dla Σm) lub 00 (dla ΠM).
    - Wykorzystanie d()d() (don't-care conditions) do tworzenia większych grup.

- Minimalizacja funkcji:
    - Wyznaczanie większych grup (ósemki, czwórki, dwójki).
    - Wyrażanie zminimalizowanej funkcji logicznej.

3. Metoda Quine’a-McCluskeya (Q-M):

- Tworzenie tabeli pierwszego rzędu:
    - Grupowanie mintermów według liczby jedynek w ich reprezentacji binarnej.

- Proces porównywania:
    - Znajdowanie i łączenie grup różniących się jedną zmienną.
    - Oznaczanie mintermów pokrytych (redukcja).

- Tabela implicantów:
    - Wyznaczanie implicantów pierwszorzędnych (ang. prime implicants).
    - Wybranie implicantów pokrywających wszystkie mintermy.