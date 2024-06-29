## Programy inspirowane wykładami z Logiki

#### Szyfrowanie XOR

[Program](./xorcipher.py) szyfrujący, deszyfrujący i podmieniający klucz gotowego szyfru za pomocą operacji XOR.
Funkcje programu:
- `-e (encode)` - Szyfruje `tekst` podany przez użytkownika za pomocą `klucza wygenerowanego` przez program
- `-d (decode)` - Deszyfruje `szyfr` podany przez użytkownika za pomocą `klucza` podanego przez użytkownika
- `-s (spoof)` - Tworzy nowy `klucz` dla `szyfru` podanego przez użytkownika, uzyskujący `żądany wynik` podany przez użytkownika

W przypadkach `-d` `-s` zakłada się, że oba podane przez użytkownika parametry są zapisane jako `tekst utf-8` bądź `grupy 8 bitów oddzielone spacjami` oraz ich długość wynosi tyle samo bajtów.

#### Logic Tree

[Program](./logictree.py) generujący drzewo binarne na podstawie podanego przez użytkownika wyrażenia logicznego w postaci standardowej.
Dotychczas napisana zamiana `notacji infiksowej` na `odwróconą notację polskią` (RPN). 
Algorytm bezpośrednio przełożony z arytmetyki na operatory logiczne z pierwszego poniższego artykułu.

TODO: zamienić `odwróconą notacje polską` na `drzewo binarne`

Znalezione zasoby:
- [Algorytm zamiany notacji infiksowej na odwróconą notację polską](https://www.geeksforgeeks.org/convert-infix-expression-to-postfix-expression)
- [Praca nt. metod zamiany notacji infiksowej na pre/postfiksową (Reverse Polish Notation Algorithm, Shunting-Yard Algorithm)](https://ieeexplore.ieee.org/abstract/document/7100228)
- [Interesujące (do zaimplementowania) -> Tree Proof Generator](https://www.umsu.de/trees/)

#### Synteza zdań logicznych

TODO: program syntezujący zdania logiczne z podanych wartości zmiennych logicznych. Jak zrobić to optymalnie, bądź najlepiej jak się da?

Znalezione zasoby:
- [Jeden ze znalezionych sposobów optymalizacji - Karnaugh Map Solver](https://www.charlie-coleman.com/experiments/kmap/)