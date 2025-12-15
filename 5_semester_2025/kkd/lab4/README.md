## Task

Napisz program, który dla nieskompresowanych obrazów zapisanych w formacie TGA1,
policzy wyniki kodowania za pomocą różnicy między predyktorami JPEG-LS (7 starych stan-
dardów i nowy standard, jako kolor otoczenia obrazka przyjmujemy czarny - RGB(0,0,0))
i poda entropię dla kodu całego obrazka jak i poszczególnych składowych koloru.
Dla porównania program powinien drukować także entropię wejściowego obrazu i en-
tropię poszczególnych składowych koloru.
Na końcu program powinien podać, która metoda jest optymalna (daje najmniejszą entro-
pię) dla danego obrazu jako całości oraz optymalne metody dla poszczególnych składowych
koloru.
Entropię program powinien liczyć tylko dla mapy bitowej (pomijamy nagłówki i stopki) a
różnice wyliczone dzięki predyktorom powinny być kodowane jako liczby 8 bitowe (operacje
(mod 256) )