# Bazy Danych

Table of Contents

- [Bazy Danych](#bazy-danych)
  - [Informacje o kursie](#informacje-o-kursie)
- [Wykład I](#wykład-i)
  - [CROSS JOIN](#cross-join)
  - [(INNER) JOIN](#inner-join)
  - [LEFT JOIN, RIGHT JOIN](#left-join-right-join)

## Informacje o kursie

- Kolokwium końcowe na przedostatnim wykładzie. (Nieobowiązkowe)
- Na ostatnim wykładzie prelekcja - elasticsearch (Rafał)

# Wykład I

## CROSS JOIN

Kobiety:

| id  | name  |
| --- | ----- |
| 1   | Anna  |
| 2   | Maria |

Mężczyźni:

| id  | name  |
| --- | ----- |
| 1   | Jan   |
| 2   | Piotr |

```sql
SELECT K.imie, M.imie FROM kobiety K CROSS JOIN mezczyzni M;
```

Rezultat:

```
Anna Jan
Anna Piotr
Maria Jan
Maria Piotr
```

Doszło do iloczynu kartezjańskiego, czyli połączenia każdego wiersza z każdym wierszem z drugiej tabeli.
W widoku wynikowym mamy 2\*2=4 wiersze, w dwóch kolumnach `K.imie` i `M.imie`.

## (INNER) JOIN

Osoby:

| id  | name   | nazwisko |
| --- | ------ | -------- |
| 1   | Jan    | Nowak    |
| 2   | Filip  | Kowalski |
| 3   | Maciej | Dutka    |

Zamówienia:

| id  | id_klienta | ... |
| --- | ---------- | --- |
| 1   | 1          | ... |
| 2   | 3          | ... |
| 3   | null       | ... |

```sql
SELECT O.imie, O.Nazwisko, Z.id FROM Osoby o INNER JOIN Zamowienia Z ON O.id = Z.id_klienta;
```

Rezultat:

| o.id | o.imie | o.nazwisko | z.id | z.id_klienta | \_JOIN  |
| ---- | ------ | ---------- | ---- | ------------ | ------- |
| 1    | Jan    | Nowak      | 1    | 1            | true    |
| 1    | Jan    | Nowak      | 2    | 3            | false   |
| 1    | Jan    | Nowak      | 3    | null         | unknown |
| 2    | Filip  | Kowalski   | 1    | 1            | false   |
| 2    | Filip  | Kowalski   | 2    | 3            | false   |
| 2    | Filip  | Kowalski   | 3    | null         | unknown |
| 3    | Maciej | Dutka      | 1    | 1            | false   |
| 3    | Maciej | Dutka      | 2    | 3            | true    |
| 3    | Maciej | Dutka      | 3    | null         | unknown |

Widzimy, że w wyniku zapytania dostaliśmy 2 wiersze, które spełniają warunek `ON O.id = Z.id_klienta`.

| o.imie | o.nazwisko | z.id |
| ------ | ---------- | ---- |
| Jan    | Nowak      | 1    |
| Maciej | Dutka      | 2    |

## LEFT JOIN, RIGHT JOIN

LEFT JOIN - Dla poprzedniego przypadku:

| o.id | o.imie | o.nazwisko | z.id | z.id_klienta | \_JOIN    |
| ---- | ------ | ---------- | ---- | ------------ | --------- |
| 1    | Jan    | Nowak      | 1    | 1            | TRUE      |
| 1    | Jan    | Nowak      | 2    | 3            | false     |
| 1    | Jan    | Nowak      | 3    | null         | unknown   |
| 2    | Filip  | Kowalski   | null | 1            | LEFT_JOIN |
| 2    | Filip  | Kowalski   | 2    | 3            | false     |
| 2    | Filip  | Kowalski   | 3    | null         | unknown   |
| 3    | Maciej | Dutka      | 1    | 1            | false     |
| 3    | Maciej | Dutka      | 2    | 3            | TRUE      |
| 3    | Maciej | Dutka      | 3    | null         | unknown   |

Wynik:

| o.imie | o.nazwisko | z.id |
| ------ | ---------- | ---- |
| Jan    | Nowak      | 1    |
| Filip  | Kowalski   | null |
| Maciej | Dutka      | 2    |

RIGHT JOIN - Dla poprzedniego przypadku:

| o.id | o.imie | o.nazwisko | z.id | z.id_klienta | \_JOIN     |
| ---- | ------ | ---------- | ---- | ------------ | ---------- |
| 1    | Jan    | Nowak      | 1    | 1            | TRUE       |
| 1    | Jan    | Nowak      | 2    | 3            | false      |
| 1    | Jan    | Nowak      | 3    | null         | unknown    |
| 2    | Filip  | Kowalski   | 1    | 1            | false      |
| 2    | Filip  | Kowalski   | 2    | 3            | false      |
| 2    | Filip  | Kowalski   | 3    | null         | unknown    |
| 3    | Maciej | Dutka      | 1    | 1            | false      |
| 3    | Maciej | Dutka      | 2    | 3            | TRUE       |
| 3    | Maciej | Dutka      | 3    | null         | unknown    |
| null | null   | null       | 3    | null         | RIGHT_JOIN |

Wynik:

| o.imie | o.nazwisko | z.id |
| ------ | ---------- | ---- |
| Jan    | Nowak      | 1    |
| Maciej | Dutka      | 2    |
| null   | null       | 3    |
