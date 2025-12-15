## Task

Napisz program który dla nieskompresowanego obrazu zapisanego w formacie TGA policzy obraz uzyskany w wyniku kwantyzacji wektorowej kolorów. Program powinien dodatkowo wypisać błąd średnio-kwadratowy dla całego obrazu oraz stosunek sygnału do szumu. Do uzyskania wymaganej liczby kolorów należy użyć algorytmu
Linndego-Buza-Graya (dla uproszczenia implementacji do mierzenia odległości między kolorami można użyć metryki taksówkowej).
Program powinien czytać trzy argumenty w linii poleceń: obraz wejściowy, obraz wyjściowy, liczba kolorów (między 0 a 24, liczba kolorów to dwójkowa potęga podanej
liczby). (Program nie musi w obrazku wyjściowym kodować mapy kolorów, może wstawić wybrane kolory bezpośrednio do obrazka.)

obcięcie: 1110....
rekonstrukcja: 11101000 <- wybieramy punkt po środku 0000-1000 (1000, lepiej nie 0111, bo długie)
