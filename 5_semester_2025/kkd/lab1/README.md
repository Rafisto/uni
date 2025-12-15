## Task

Dla dyskretnych zmiennych losowych X i Y entropia Y warunkowana przez X jest określona wzorem

$$
H(Y|X)= \sum_{x\in X} P(x) \cdot H(Y|x)
$$

gdzie

$$
H(Y|x) = \sum_{y\in Y} P(y|x) \cdot I(y|x)
$$

a $P(z)$ oznacza prawdopodobieństwo z a $I(z)$ informację związaną z $z$.
Napisz program który dla podanego pliku traktowanego jako ciąg 8-bitowych symboli
policzy częstość występowania tych symboli oraz częstość występowania symboli po danym
symbolu (częstość występowania pod warunkiem, że poprzedni znak jest dany, dla pierwszego
znaku przyjmij, że przed nim jest znak o kodzie 0). Dopisz funkcję, która dla policzonych
częstości traktowanych jako zmienne losowe policzy entropię i entropię warunkową (warun-
kowaną znajomością poprzedniego symbolu), oraz poda różnicę między nimi.
Program ma działać z linii poleceń, czytać plik podany jako argument wywołania, oraz
wypisywać wyniki w sposób czytelny i łatwy do dalszego przetwarzania.
Przeanalizuj wyniki działania swojego programu dla przykładowych plików tekstowych,
doc, pdf, mp4 czy jpg (weź pliki o rozmiarze co najmniej 1MB).