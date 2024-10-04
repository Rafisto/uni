1. Podaj nazwiska wszystkich prezesów. Podaj nazwiska prezesów, unikając powtórzeń.

```sql
SELECT Nazwisko_prezesa FROM Firma;
SELECT DISTINCT Nazwisko_prezesa FROM Firma;
```

2. Podaj nazwy wszystkich firm założonych przed 2000-01-01.

```sql
SELECT Nazwa FROM Firma WHERE Data_zalozenia < '2000-01-01'; 
```

3. Wyświetl firmy zatrudniające przynajmniej 10 pracowników.

Zatrudniały podczas całego działania

```sql
SELECT Nazwa_firmy, COUNT(Nazwa_firmy)
FROM Zatrudnienie 
GROUP BY Nazwa_firmy
HAVING COUNT(Nazwa_firmy) > 1;
```

Zatrudniają obecnie:

```sql
SELECT Nazwa_firmy, COUNT(Nazwa_firmy)
FROM Zatrudnienie
WHERE Data_zwolnienia IS NULL
GROUP BY Nazwa_firmy
HAVING COUNT(Nazwa_firmy) > 0;
```

4. Wyświetl nazwiska tych prezesów, którzy widnieją jako pracownicy własnej firmy.

5. Wyświetl nazwy wszystkich firm, imię i nazwisko prezesa każdej oraz miesiąc i rok, w których firma zanotowała stratę (wydatki przekroczyły przychody).
6. Dla wszystkich firm, których prezes ma na nazwisko Kowalski, podaj ich nazwę i roczne obroty, czyli rok i zysk bądź stratę (w uproszczeniu: przychód - wydatki).
7. Wyświetl imiona i nazwiska prezesów oraz nazwy firm, które nie zatrudniają pracownika o nazwisku Fikcyjny.
8. Wypisz wszystkie firmy, zawierające w swojej nazwie sp. z o.o.
9.  Podaj nazwę oraz rok założenia najstarszej firmy. Co się dzieje w przypadku, gdy kilka firm zostało założonych w tym samym roku?
10. Wypisz wszystkie firmy, które nie zatrudniają żadnego pracownika.
11. Wypisz wszystkie firmy, które zostały założone wcześniej niż Korepetycje sp. z o.o.?
12. Wyświetl imiona wszystkich pracowników o nazwisku Kowalski lub Nowak, zadbaj o brak powtórzeń.
13. Znajdź firmy, które zarobiły najwięcej w pierwszym roku kalendarzowym swojego istnienia.
14. Wypisz nazwy firm, które w przeciągu ostatniego roku przyniosły stratę. Napisz zapytanie tak, by niezależnie od aktualnej daty zawsze uwzględniało poprzedni rok kalendarzowy.
15. Znajdź pary firm, które mają ten sam adres. Jeżeli pojawia się krotka (X, Y), zadbaj, by nie wyświetlała się krotka (Y, X).
16. Dla każdej firmy znajdź sumę jej wydatków w pierwszych 6 miesiącach każdego roku.
17. Wypisz nazwy firm wraz z rokiem ich założenia, wyniki uporządkuj chronologicznie.
18. Wypisz alfabetycznie nazwy firm, w których pracują Jan Kowalski lub Jan Nowak, zadbaj o brak powtórzeń.
19. Korzystając z tabeli Obroty, uszereguj miesiące i lata pod względem największego łącznego przychodu wszystkich firm. W razie jednakowych łącznych przychodów, miesiące powinny być uszeregowane od najnowszego.
20. Dla każdej firmy wypisz liczbę zatrudnionych przez nią pracowników.
21. Znajdź nazwę firmy zatrudniającej największą liczbę pracowników o tym samym nazwisku, co jej prezes.
22. Uszereguj firmy malejąco pod względem największego średniego zarobku (przychód - wydatki) przypadającego na pracownika w marcu 2017.