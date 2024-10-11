## DB Query Execution Precedence

From first to last operation:
- JOIN
- WHERE
- GROUP BY
- HAVING
- SELECT

You must use aliases when joining tables with the same name

1. Podaj nazwiska wszystkich prezesów. Podaj nazwiska prezesów, unikając powtórzeń.

```sql
SELECT Nazwisko_prezesa FROM Firma;
SELECT DISTINCT Nazwisko_prezesa FROM Firma;
```

2. Podaj nazwy wszystkich firm założonych przed 2000-01-01.

```sql
SELECT Nazwa 
FROM Firma 
WHERE Data_zalozenia < '2000-01-01';
```

3. Wyświetl firmy zatrudniające przynajmniej 10 pracowników.

Zatrudniały podczas całego działania:

```sql
SELECT Nazwa_firmy
FROM Zatrudnienie
GROUP BY Nazwa_firmy
HAVING COUNT(Nazwa_firmy) >= 10;
```

Zatrudniają obecnie:

```sql
SELECT Nazwa_firmy
FROM Zatrudnienie
WHERE Data_zwolnienia IS NULL
GROUP BY Nazwa_firmy
HAVING COUNT(Nazwa_firmy) >= 10;
```

Upgrade: z zatrudnieniem:

```sql
SELECT Firma.* 
FROM Firma
INNER JOIN Zatrudnienie ON Firma.Nazwa = Zatrudnienie.Nazwa_firmy
WHERE Zatrudnienie.Data_zwolnienia IS NULL
GROUP BY Zatrudnienie.Nazwa_firmy
HAVING COUNT(Id_pracownika) >= 10;
```

1. Wyświetl nazwiska tych prezesów, którzy widnieją jako pracownicy własnej firmy.

```sql
SELECT DISTINCT F.Nazwisko_prezesa
FROM Firma F
JOIN Pracownicy P ON F.Pesel_prezesa = P.Pesel;
```

Upgrade: Aktualni pracownicy:

```sql
SELECT DISTINCT F.Nazwisko_prezesa
FROM Firma F
JOIN Pracownicy P ON F.Pesel_prezesa = P.Pesel
JOIN Zatrudnienie Z ON F.Nazwa = Z.Nazwa_firmy
WHERE Z.Data_zwolnienia IS NULL;
```

5. Wyświetl nazwy wszystkich firm, imię i nazwisko prezesa każdej oraz miesiąc i rok, w których firma zanotowała stratę (wydatki przekroczyły przychody).

```sql
SELECT F.Nazwa, F.Imie_prezesa, F.Nazwisko_prezesa, O.Rok, O.Miesiac
FROM Firma F
JOIN Obroty O ON F.Nazwa = O.Nazwa_firmy
WHERE O.Przychod < O.Wydatki;
```

6. Dla wszystkich firm, których prezes ma na nazwisko Kowalski, podaj ich nazwę i roczne obroty, czyli rok i zysk bądź stratę (w uproszczeniu: przychód - wydatki).

```sql
SELECT F.Nazwa, O.Rok, SUM(O.Przychod - O.Wydatki) AS Obroty
FROM Firma F
JOIN Obroty O ON F.Nazwa = O.Nazwa_firmy
WHERE F.Nazwisko_prezesa = 'Kowalski'
GROUP BY F.Nazwa, O.Rok;
```

7. Wyświetl imiona i nazwiska prezesów oraz nazwy firm, które nie zatrudniają pracownika o nazwisku `Nazwiskowy`.

```sql
SELECT F.Imie_prezesa, F.Nazwisko_prezesa, F.Nazwa
FROM Firma F
WHERE NOT EXISTS (
    SELECT 1
    FROM Zatrudnienie Z
    JOIN Pracownicy P ON Z.Id_pracownika = P.Id
    WHERE Z.Nazwa_firmy = F.Nazwa AND P.Nazwisko = 'Nazwiskowy' AND Z.Data_zwolnienia IS NULL
);
```

```sql
SELECT *
FROM Firma F
LEFT JOIN Zatrudnienie Z ON F.Nazwa = Z.Nazwa_firmy;
```

Pomysł Michała:

```sql
SELECT Firma.Nazwa, Firma.Imie_prezesa, Firma.nazwisko_prezesa
FROM Firma
WHERE Firma.Nazwa NOT IN (
    SELECT Zatrudnienie.Nazwa_firmy
    FROM Pracownicy
    JOIN Zatrudnienie
    ON Pracownicy.Id = Zatrudnienie.Id_pracownika 
    WHERE Pracownicy.Nazwisko = "Nazwiskowy" OR Zatrudnienie.Data_zwolnienia IS NULL
);
```

8. Wypisz wszystkie firmy, zawierające w swojej nazwie sp. z o.o.

```sql
SELECT Nazwa
FROM Firma
WHERE Nazwa LIKE '%sp. z o.o.%';
```

9.  Podaj nazwę oraz rok założenia najstarszej firmy. Co się dzieje w przypadku, gdy kilka firm zostało założonych w tym samym roku?

```sql
SELECT Nazwa, Data_zalozenia
FROM Firma
WHERE Data_zalozenia = (
    SELECT MIN(Data_zalozenia) FROM Firma
);
```

Pokaże wszyskie takie firmy.

10. Wypisz wszystkie firmy, które nie zatrudniają żadnego pracownika.

Nigdy nie zatrudniały:

```sql
SELECT F.Nazwa
FROM Firma F
LEFT JOIN Zatrudnienie Z ON F.Nazwa = Z.Nazwa_firmy
WHERE Z.Id_pracownika IS NULL;
```

Aktualnie nie zatrudniają:

```sql
SELECT F.Nazwa
FROM Firma F
WHERE Nazwa NOT IN (
    SELECT Nazwa_firmy 
    FROM Zatrudnienie
    WHERE Data_zwolnienia IS NULL
);
```

11. Wypisz wszystkie firmy, które zostały założone wcześniej niż `Korepetycje sp. z o.o.?`

```sql
SELECT Nazwa
FROM Firma
WHERE Data_zalozenia < (
    SELECT Data_zalozenia
    FROM Firma
    WHERE Nazwa = 'Korepetycje sp. z o.o.'
);
```

12. Wyświetl imiona wszystkich pracowników o nazwisku Kowalski lub Nowak, zadbaj o brak powtórzeń.

```sql
SELECT DISTINCT Imie
FROM Pracownicy
WHERE Nazwisko IN ('Kowalski', 'Nowak');
```

13. Znajdź firmy, które zarobiły najwięcej w pierwszym roku kalendarzowym swojego istnienia.

```sql
SELECT Nazwa_firmy, SUM(Przychod - Wydatki) AS Zysk
FROM Obroty O
JOIN Firma F ON O.Nazwa_firmy = F.Nazwa
WHERE O.Rok = YEAR(F.Data_zalozenia)
GROUP BY Nazwa_firmy
ORDER BY Zysk DESC;
```

Update Pomysł Michała:

```sql
SELECT Firma.*
FROM Firma
JOIN Obroty
ON Firma.Nazwa = Obroty.Nazwa_firmy
WHERE MIN(Obroty.Rok) IN (
    SELECT Obroty.Nazwa_firmy, Obroty.Rok, MAX(Obroty.Przychod - Obroty.Wydatki)
    FROM Obroty;
)
GROUP BY Firma.Nazwa;
```

14. Wypisz nazwy firm, które w przeciągu ostatniego roku przyniosły stratę. Napisz zapytanie tak, by niezależnie od aktualnej daty zawsze uwzględniało poprzedni rok kalendarzowy.

```sql
SELECT Nazwa_firmy
FROM Obroty
WHERE Rok = YEAR(CURDATE()) - 1
GROUP BY Nazwa_firmy
HAVING SUM(Przychod) < SUM(Wydatki);
```

15. Znajdź pary firm, które mają ten sam adres. Jeżeli pojawia się krotka (X, Y), zadbaj, by nie wyświetlała się krotka (Y, X).

```sql
SELECT F1.Nazwa AS Firma1, F2.Nazwa AS Firma2, F1.Adres
FROM Firma F1
JOIN Firma F2 ON F1.Adres = F2.Adres AND F1.Nazwa < F2.Nazwa;
```

16. Dla każdej firmy znajdź sumę jej wydatków w pierwszych 6 miesiącach każdego roku.

```sql
SELECT Nazwa_firmy, Rok, SUM(Wydatki) AS Suma_wydatkow
FROM Obroty
WHERE Miesiac BETWEEN 1 AND 6
GROUP BY Nazwa_firmy, Rok;  
```

17. Wypisz nazwy firm wraz z rokiem ich założenia, wyniki uporządkuj chronologicznie.

```sql
SELECT Nazwa, YEAR(Data_zalozenia) AS Rok_zalozenia
FROM Firma
ORDER BY Data_zalozenia;
```

18. Wypisz alfabetycznie nazwy firm, w których pracują Jan Kowalski lub Jan Nowak, zadbaj o brak powtórzeń.

```sql
SELECT DISTINCT F.Nazwa
FROM Firma F
JOIN Zatrudnienie Z ON F.Nazwa = Z.Nazwa_firmy
JOIN Pracownicy P ON Z.Id_pracownika = P.Id
WHERE (P.Imie = 'Jan' AND P.Nazwisko IN ('Kowalski', 'Nowak'))
ORDER BY F.Nazwa;
```

19. Korzystając z tabeli Obroty, uszereguj miesiące i lata pod względem największego łącznego przychodu wszystkich firm. W razie jednakowych łącznych przychodów, miesiące powinny być uszeregowane od najnowszego.

```sql
SELECT Rok, Miesiac, SUM(Przychod) AS Laczny_przychod
FROM Obroty
GROUP BY Rok, Miesiac
ORDER BY Laczny_przychod DESC, Rok DESC, Miesiac DESC;
```

20. Dla każdej firmy wypisz liczbę zatrudnionych przez nią pracowników.

```sql
SELECT Nazwa_firmy, COUNT(Id_pracownika) AS Liczba_pracownikow
FROM Zatrudnienie
GROUP BY Nazwa_firmy;
```

21. Znajdź nazwę firmy zatrudniającej największą liczbę pracowników o tym samym nazwisku, co jej prezes.

```sql
SELECT F.Nazwa
FROM Firma F
JOIN Zatrudnienie Z ON F.Nazwa = Z.Nazwa_firmy
JOIN Pracownicy P ON Z.Id_pracownika = P.Id
WHERE P.Nazwisko = F.Nazwisko_prezesa
GROUP BY F.Nazwa
ORDER BY COUNT(P.Id) DESC
LIMIT 1;
```

22. Uszereguj firmy malejąco pod względem największego średniego zarobku (przychód - wydatki) przypadającego na pracownika w marcu 2017.

```sql
SELECT O.Nazwa_firmy, AVG(O.Przychod - O.Wydatki) AS Sredni_zarobek
FROM Obroty O
JOIN Zatrudnienie Z ON O.Nazwa_firmy = Z.Nazwa_firmy
WHERE O.Rok = 2017 AND O.Miesiac = 3
GROUP BY O.Nazwa_firmy
ORDER BY Sredni_zarobek DESC;
```
