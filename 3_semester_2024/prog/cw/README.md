```bash
yay -S plantuml
rm *.png
plantuml *.puml 
```

## Zadanie 1

![zadanie](./zadanie1.png)

## Zadanie 2

![zadanie](./zadanie2.png)

## Zadanie 3

<details>

### 1. **Kurs**
   - **Definicja**: Kurs to jednostka dydaktyczna w systemie, która obejmuje określoną liczbę godzin zajęć oraz tematykę. Jest to przedmiot, który student musi zrealizować w trakcie studiów.
   - **Przykład**: Kurs „Matematyka 1” to cykl wykładów i ćwiczeń, które student musi zaliczyć, aby zdobyć punkty ECTS.

### 2. **Grupa kursów**
   - **Definicja**: Zbiór kursów, które są powiązane tematycznie lub funkcjonalnie. Grupa kursów może zawierać kilka przedmiotów do wyboru, z których student musi zrealizować jeden lub więcej, aby spełnić wymagania programu studiów.
   - **Przykład**: Grupa kursów „Przedmioty fakultatywne” może obejmować kursy z różnych dziedzin, takich jak „Psychologia”, „Filozofia”, i „Socjologia”, z których student wybiera jeden.

### 3. **Grupa zajęciowa**
   - **Definicja**: To podgrupa studentów zapisanych na dany kurs, którzy uczęszczają na zajęcia w określonych terminach i godzinach. Każda grupa zajęciowa może mieć własny plan zajęć i prowadzącego.
   - **Przykład**: W kursie „Fizyka” student może wybrać grupę zajęciową, która odbywa zajęcia w poniedziałki o 8:00 lub inną grupę, która spotyka się w środy o 10:00.

### 4. **ECTS**
   - **Definicja**: Punkty ECTS (European Credit Transfer and Accumulation System) to jednostka miary, która określa ilość pracy potrzebnej do zaliczenia danego kursu. ECTS ułatwia porównanie osiągnięć studentów między różnymi uczelniami.
   - **Przykład**: Kurs „Algorytmy i struktury danych” może mieć wartość 5 ECTS, co oznacza określoną liczbę godzin nauki i zaliczenia.

### 5. **Rejestracja na kursy**
   - **Definicja**: Proces, w którym studenci wybierają kursy i grupy zajęciowe, na które chcą uczęszczać w danym semestrze. Rejestracja odbywa się online w systemie UsosWeb i jest ograniczona czasowo.
   - **Przykład**: Rejestracja na semestr zimowy otwiera się 1 września i zamyka 15 września, a student musi wybrać kursy zgodne z planem studiów.

### 6. **Plan zajęć**
   - **Definicja**: Zbiór informacji o terminach i miejscach, w których odbywają się zajęcia danego kursu. Plan zawiera daty wykładów, ćwiczeń, laboratoriów i innych form zajęć.
   - **Przykład**: Plan zajęć dla kursu „Programowanie w Pythonie” może obejmować wykład w czwartki od 12:00 do 14:00 oraz ćwiczenia w piątki od 10:00 do 12:00.

### 7. **Podanie**
   - **Definicja**: Dokument, który student składa do władz uczelni w celu załatwienia formalności związanych z różnymi aspektami studiów, np. przedłużenie sesji egzaminacyjnej, zaliczenie warunkowe.
   - **Przykład**: Student może złożyć podanie o przedłużenie terminu oddania pracy dyplomowej.

### 8. **Stypendium**
   - **Definicja**: Pomoc finansowa przyznawana studentom spełniającym określone kryteria, np. stypendium naukowe, socjalne lub specjalne. Wnioski o stypendia są składane i przetwarzane w systemie UsosWeb.
   - **Przykład**: Student z wysoką średnią może ubiegać się o stypendium rektora.

### 9. **Ocena**
   - **Definicja**: Wynik, jaki student otrzymuje za realizację danego kursu. Oceny są wpisywane do systemu UsosWeb i są podstawą do obliczenia średniej ocen na studiach.
   - **Przykład**: Za egzamin z kursu „Chemia” student może otrzymać ocenę 5,0.

### 10. **Konsultacje**
   - **Definicja**: Terminy, w których studenci mogą spotkać się z prowadzącymi kursy, aby omówić pytania lub problemy związane z materiałem dydaktycznym. Konsultacje są zwykle planowane raz w tygodniu.
   - **Przykład**: Prowadzący kurs „Analiza matematyczna” oferuje konsultacje w każdy wtorek od 14:00 do 16:00.

### 11. **Indeks**
   - **Definicja**: Rejestr osiągnięć studenta, który zawiera informacje o zaliczonych kursach i otrzymanych ocenach. W systemie UsosWeb indeks jest w formie elektronicznej.
   - **Przykład**: W indeksie studenta można znaleźć zaliczone kursy z poprzednich semestrów wraz z ocenami.

### 12. **Dziekanat**
   - **Definicja**: Jednostka administracyjna uczelni odpowiedzialna za obsługę studentów, np. za rejestrację na studia, składanie podań i wydawanie dokumentów. Wiele spraw w dziekanacie można załatwić online przez UsosWeb.
   - **Przykład**: Student może zgłosić się do dziekanatu po odebranie dyplomu ukończenia studiów.

</details>

## Zadanie 4

![zadanie](./zadanie4.png)

## Zadanie 5

<details>

Oto przykładowe wymagania funkcjonalne dla modułu sprzedaży dla sklepu na stacji benzynowej:

### 1. Obsługa produktów:
   - Dodawanie, edytowanie i usuwanie produktów dostępnych w sklepie (np. napoje, przekąski, produkty higieniczne).
   - Zarządzanie kategoriami produktów (np. napoje, żywność, akcesoria samochodowe).
   - Obsługa zmiennej ilości produktów na stanie (np. aktualizacja stanów magazynowych).

### 2. Proces sprzedaży:
   - Rejestracja transakcji sprzedaży z poziomu terminala kasowego.
   - Możliwość skanowania kodów kreskowych produktów.
   - Obsługa różnych metod płatności (gotówka, karta, płatności mobilne).
   - Generowanie paragonów fiskalnych lub faktur VAT dla klientów.
   - Obsługa rabatów, kuponów i promocji na wybrane produkty lub kategorie.

### 3. Zarządzanie płatnościami:
   - Weryfikacja i przetwarzanie płatności gotówkowych oraz kartowych (integracja z terminalem płatniczym).
   - Możliwość zwrotu środków (obsługa zwrotów produktów i anulowania transakcji).

### 4. Raportowanie i statystyki:
   - Generowanie dziennych, tygodniowych i miesięcznych raportów sprzedaży.
   - Możliwość śledzenia najczęściej sprzedawanych produktów.
   - Raporty dotyczące sprzedaży w podziale na kategorie produktów.
   - Analiza rentowności i marży produktów.

### 5. Integracja z systemem magazynowym:
   - Automatyczne aktualizowanie stanów magazynowych po każdej sprzedaży.
   - Powiadomienia o niskich stanach magazynowych produktów.
   - Możliwość ręcznego uzupełniania stanów magazynowych.

### 6. Obsługa pracowników:
   - Logowanie pracowników do systemu sprzedaży (różne poziomy dostępu w zależności od roli).
   - Historia transakcji wykonywanych przez poszczególnych pracowników.
   - Obsługa zmian kasowych (raportowanie i rozliczanie kas).

### 7. Integracja z systemem lojalnościowym:
   - Rejestrowanie punktów lojalnościowych przy zakupie.
   - Obsługa kart lojalnościowych klientów.
   - Możliwość wymiany punktów na produkty lub rabaty.

### 8. Współpraca z dystrybutorem paliw:
   - Rejestrowanie sprzedaży paliwa na stacji.
   - Powiązanie sprzedaży produktów z tankowaniem (np. rabaty przy zakupie paliwa).

### 9. Obsługa rezerwacji i zamówień:
   - Możliwość rezerwacji produktów przez klientów (odbiór na stacji).
   - Integracja z zamówieniami online (odbiór w sklepie stacjonarnym).

### 10. Zgodność z przepisami:
   - Obsługa przepisów dotyczących sprzedaży alkoholu i wyrobów tytoniowych (np. weryfikacja wieku klienta).
   - Spełnianie wymogów fiskalnych i prawnych związanych z prowadzeniem sklepu.

Czy to odpowiada Twoim potrzebom?

</details>

## Zadanie 6

![zadanie](./zadanie6.png)

## Zadanie 7

![zadanie](./zadanie7.png)