Zadanie 1.

```sql
SELECT 
F1.Tytul, F1.RokPremiery, F2.RokPremiery, F2.RokPremiery_2
FROM Film F1
JOIN Film F2 ON F1.Tytul = F2.Tytul AND F1.RokPremiery < F2.RokPremiery;
```



Zadanie 2.

```sql
SELECT 
    F.Tytul, F.RokPremiery, A.Imie, A.Nazwisko
FROM Film F
JOIN Rezyser R ON F.Rezyser = R.Id
WHERE F.Tytul IN (
    SELECT F.Tytul
    FROM Film F
    JOIN Rezyser R ON F.Rezyser = R.Id
    JOIN Obsada O ON F.Tytul = O.Film
    JOIN Aktor A ON O.Aktor = A.Id
    WHERE F.Rezyser IN (
        SELECT A.Id
        FROM Aktor A
        JOIN Obsada O ON A.Id = O.Aktor
        JOIN Film F ON O.Film = F.Tytul
        JOIN Rezyser R ON F.Rezyser = R.Id
    )
);
```

$A=Rezyser \bowtie \rho_{Rezyser->ID} (Film)$
$B=A \bowtie \rho_{Film -> Tytul, Aktor->ID} (Obsada)$
$\pi_{Film->Tytul} (B \bowtie \rho_{Aktor->ID} (Aktor))$
$C=\pi_{Rezyser->ID} (A \bowtie \rho_{Rezyser->ID} (Film))$

Zadanie 3.

Directors which are actors in any movie.

```sql
SELECT
    f.Tytul AS TytulFilmu,
    r.Imie AS ImieRezysera,
    r.Nazwisko AS NazwiskoRezysera
FROM Film f
JOIN Rezyser r ON f.Rezyser = r.Id
JOIN Obsada o ON f.Tytul = o.Film
JOIN Aktor a ON o.Aktor = a.Id
WHERE r.Id = a.Id;
```

$\pi_{Tytul, Imie, Nazwisko}((Film \bowtie_{Rezyser = Id} Rezyser) \bowtie_{Tytul = Film} Obsada \bowtie_{Id = Aktor} Aktor)$

Zadanie 4.

Reżyserowie którzy wyrezyserowali więcej niż przeciętna liczba filmów, posortowana po wieku reżysera

```sql
SELECT
    r.Imie AS ImieRezysera,
    r.Nazwisko AS NazwiskoRezysera,
    r.Wiek AS WiekRezysera,
    COUNT(f.Tytul) AS LiczbaFilmow
FROM Film f 
JOIN Rezyser r ON f.Rezyser = r.Id
GROUP BY r.Imie, r.Nazwisko, r.Wiek
HAVING COUNT(f.Tytul) > (
    SELECT AVG(LiczbaFilmow) AS Srednia
    FROM (
        SELECT COUNT(f.Tytul) AS LiczbaFilmow 
        FROM Film f JOIN Rezyser r ON f.Rezyser = r.Id 
        GROUP BY r.Imie, r.Nazwisko) AS T
    )
ORDER BY r.Wiek ASC;
```

Weźmy liczbę filmów wyreżyserowanych przez każdego reżysera:

$a=(\gamma_{COUNT(Tytul)}(Film \bowtie_{Rezyser = Id} Rezyser))$

Następnie weźmy średnią z tych liczb:

$b=\gamma_{AVG(LiczbaFilmow)}(\pi_{LiczbaFilmow}(a))$

Ostatecznie wybierzmy reżyserów, którzy wyreżyserowali więcej filmów niż średnia:

$c=\tau_{Wiek ASC}(\pi_{Imie, Nazwisko, Wiek, COUNT(Tytul)}(\sigma_{COUNT(Tytul)} (Film \bowtie_{Rezyser = Id} Rezyser) > b))$

Zadanie 10.

```sql
SELECT Obsada.Film, COUNT(Obsada.Aktor) AS LiczbaAktorow
FROM Obsada
GROUP BY Obsada.Film
ORDER BY LiczbaAktorow DESC
```

$\tau_{COUNT(Aktor) DESC} (\gamma_{COUNT(Aktor)}(\pi_{Film, Aktor}(Obsada)))$

Zadanie 13.

```sql
SELECT Tytul, RokPremiery, Budzet, Przychod, (Budzet - Przychod) AS Strata
FROM Film
WHERE Przychod < Budzet
ORDER BY Budzet DESC;
```

$\tau_{\text{Budzet DESC}} (\rho_{\text{Budzet - Przychod AS Strata}} (\pi_{\text{Tytul, RokPremiery, Budzet, Przychod, Budzet - Przychod}} (\sigma_{Przychod < Budzet} (Film))))$
