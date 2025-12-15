## Task

Napisz program kodujący i program dekodujący dany plik wejściowy na dany plik wyj-
ściowy. Program kodujący powinien dodatkowo na koniec zwrócić na ekran odpowiednio
entropię kodowanych danych, średnią długość kodowania i stopień kompresji. Alfabetem
danych pierwotnych są bajty (8-bitowe znaki).
Program może być napisany w dowolnym języku programowania, ale jego czas działania
dla testów z poprzedniej listy nie powinien przekraczać 30 sekund. Programy powinny być
wywoływane z linii poleceń z podanymi nazwami plików jako argumentami wywołania.
Należy wybrać jeden z wariantów:

1. Programy mają używać klasycznego kodowania Huffmana i w czasie kompresji
dodawać odpowiednio zapamiętany słownik umożliwiający dekompresję.
2. Programy mają używać dynamicznych kodów Huffmana.
3. **Programy mają używać adaptacyjnego kodowania arytmetycznego ze skalowa-
niem.**