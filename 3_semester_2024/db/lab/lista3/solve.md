# Lab 3

## Rafał Włodarczyk

### 2024-12-03

- [Lab 3](#lab-3)
  - [Rafał Włodarczyk](#rafał-włodarczyk)
    - [2024-12-03](#2024-12-03)
  - [Solves](#solves)
    - [Exercise 1](#exercise-1)

MariaDB Setup:

```yaml
services:
  mariadb:
    image: mariadb:latest
    container_name: mariadb-container
    environment:
      MYSQL_ROOT_PASSWORD: rootpassword
      MYSQL_DATABASE: db2024
      MYSQL_USER: rafisto
      MYSQL_PASSWORD: rafistopassword
    volumes:
      - db_data:/var/lib/mysql

    ports:
      - "3306:3306"
    networks:
      - mariadb-network

volumes:
  db_data:

networks:
  mariadb-network:
    driver: bridge
```

```bash
# Maintenance

## Up DB
docker compose up -d
## Down DB
docker compose down && docker volume rm lista3_db_data

# Execution

## Root user
docker exec -it mariadb-container mariadb -D db2024 -u root -prootpassword
```

## Solves

### Exercise 1

Utwórz nową bazę danych o dowolnej nazwie a w niej tabele:

- Ludzie (PESEL: char(11), imie: varchar(30), nazwisko: varchar(30),
  data_urodzenia: date, plec: enum('K', 'M'))
- Zawody (zawod*id: int, nazwa: varchar(50), pensja_min: float,
  pensja* max: float)
- Pracownicy (PESEL: char(11), zawod_id: int, pensja: float)

Tworzę bazę `db2024` oraz tabele `Ludzie`, `Zawody` and `Pracownicy`:

```sql
USE db2024;

-- ValidatePesel function
DELIMITER $$
CREATE FUNCTION ValidatePESEL(pesel CHAR(11)) 
RETURNS BOOLEAN
DETERMINISTIC
BEGIN
    -- Check if the input is exactly 11 digits
    IF LENGTH(pesel) != 11 OR pesel NOT REGEXP '^[0-9]{11}$' THEN
        RETURN FALSE;
    END IF;

    -- Define weights and initialize checksum
    SET @weights = '1379137913';
    SET @checksum = 0;

    -- Calculate checksum
    SET @i = 1;
    WHILE @i <= 10 DO
        SET @checksum = @checksum + 
            (CAST(SUBSTRING(pesel, @i, 1) AS UNSIGNED) * 
             CAST(SUBSTRING(@weights, @i, 1) AS UNSIGNED));
        SET @i = @i + 1;
    END WHILE;

    SET @checksum = (10 - (@checksum MOD 10)) MOD 10;

    -- Compare calculated checksum with the last digit of PESEL
    IF @checksum = CAST(SUBSTRING(pesel, 11, 1) AS UNSIGNED) THEN
        RETURN TRUE;
    ELSE
        RETURN FALSE;
    END IF;
END$$
DELIMITER ;



-- Ludzie (PESEL: char(11), imie: varchar(30), nazwisko: varchar(30),
-- data_urodzenia: date, plec: enum('K', 'M'))

CREATE TABLE Ludzie (
    PESEL char(11) PRIMARY KEY,
    imie varchar(30),
    nazwisko varchar(30),
    data_urodzenia date,
    plec enum('K', 'M')
);


-- PESEL jest zdefiniowany jako `char(11)`. Należy dopisać funkcje sprawdzającą poprawność numeru PESEL.
-- Trigger to validate the PESEL number
-- on insert into Ludzie table

DELIMITER $$
CREATE TRIGGER ValidatePESELTrigger
BEFORE INSERT ON Ludzie
FOR EACH ROW
BEGIN
    DECLARE isValid INT;
    SET isValid = ValidatePESEL(NEW.PESEL);
    IF isValid = FALSE THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Invalid PESEL';
    END IF;
END$$
DELIMITER ;

-- Zawody (zawod_id: int, nazwa: varchar(50), pensja_min: float,
-- pensja_ max: float)

-- Dopilnuj, by nie można było wprowadzić także ujemnych wartości liczbowych do bazy oraz aby pensja_min < pensja_max.

CREATE TABLE Zawody (
    zawod_id int PRIMARY KEY,
    nazwa varchar(50),
    pensja_min float CHECK (pensja_min >= 0),
    pensja_max float CHECK (pensja_max > pensja_min)
);

-- Pracownicy (PESEL: char(11), zawod_id: int, pensja: float)

CREATE TABLE Pracownicy (
    PESEL char(11),
    zawod_id int,
    pensja float CHECK (pensja >= 0),
    PRIMARY KEY (PESEL, zawod_id),
    FOREIGN KEY (PESEL) REFERENCES Ludzie(PESEL),
    FOREIGN KEY (zawod_id) REFERENCES Zawody(zawod_id)
);

-- Trigger to validate if pensja is in range of pensja_min and pensja_max in Zawody table
-- on insert into Pracownicy table

DELIMITER $$
CREATE TRIGGER ValidatePensjaTrigger
BEFORE INSERT ON Pracownicy
FOR EACH ROW
BEGIN
    DECLARE minPensja float;
    DECLARE maxPensja float;

    SELECT pensja_min, pensja_max INTO minPensja, maxPensja
    FROM Zawody
    WHERE zawod_id = NEW.zawod_id;

    IF NEW.pensja < minPensja OR NEW.pensja > maxPensja THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Pensja is out of range';
    END IF;
END$$
DELIMITER ;
```

Czy dobrym pomysłem jest stosowanie nr PESEL jako klucza? Jeżeli uważasz, że nie, popraw to.

```
PESEL jako klucz jest dobrym pomysłem, ponieważ jest to unikalny numer identyfikacyjny dla każdej osoby w Polsce.
```

Do tabeli Ludzie wprowadź informacje na temat:

- 5 osób niepełnoletnich
- 45 osób pełnoletnich, ale mających zarazem mniej niż 60 lat oraz
- 5 osób w wieku co najmniej 60 lat.

```sql
-- bad pesel
INSERT INTO Ludzie (PESEL, imie, nazwisko, data_urodzenia, plec) VALUES
("00000000001", "Jan", "Kowalski", "2000-01-01", "M");

-- niepelnoletni (urodzeni w 2020 roku)
INSERT INTO Ludzie (PESEL, imie, nazwisko, data_urodzenia, plec) VALUES
("20250352229", "Jan", "Kowalski", "2020-01-01", "M"),
("20240988645", "Anna", "Nowak", "2020-02-02", "K"),
("20210665727", "Piotr", "Wiśniewski", "2020-03-03", "M"),
("20290314391", "Zofia", "Dąbrowska", "2020-04-04", "K"),
("20241092938", "Maria", "Lewandowska", "2020-05-05", "K");

-- pelnoletni (mniej niz 60 lat)
INSERT INTO Ludzie (PESEL, imie, nazwisko, data_urodzenia, plec) VALUES
("97041719691", "Adam", "Nowak", "1997-04-17", "M"),
("91091646426", "Ewa", "Kowalska", "1991-09-16", "K"),
("96110957767", "Piotr", "Wiśniewski", "1996-11-09", "M"),
("90012218753", "Anna", "Wójcik", "1990-01-22", "K"),
("92112662672", "Marek", "Kowalczyk", "1992-11-26", "M"),
("96123193569", "Katarzyna", "Kamińska", "1996-12-31", "K"),
("99041958393", "Tomasz", "Lewandowski", "1999-04-19", "M"),
("98112451423", "Agnieszka", "Zielińska", "1998-11-24", "K"),
("96081447663", "Paweł", "Szymański", "1996-08-14", "M"),
("98012855439", "Monika", "Woźniak", "1998-01-28", "K"),
("97071114468", "Łukasz", "Dąbrowski", "1997-07-11", "M"),
("90112354171", "Joanna", "Kozłowska", "1990-11-23", "K"),
("98041188535", "Michał", "Jankowski", "1998-04-11", "M"),
("90052587741", "Magdalena", "Mazur", "1990-05-25", "K"),
("90102676254", "Rafał", "Krawczyk", "1990-10-26", "M"),
("92072765217", "Dorota", "Piotrowska", "1992-07-27", "K"),
("94070719854", "Grzegorz", "Grabowski", "1994-07-07", "M"),
("95071995571", "Sylwia", "Pawlak", "1995-07-19", "K"),
("90110243295", "Krzysztof", "Michalski", "1990-11-02", "M"),
("94052393539", "Beata", "Nowicka", "1994-05-23", "K"),
("90101783542", "Wojciech", "Adamczyk", "1990-10-17", "M"),
("95122189245", "Alicja", "Dudek", "1995-12-21", "K"),
("94062483824", "Sebastian", "Zawadzki", "1994-06-24", "M"),
("93031773427", "Natalia", "Sikora", "1993-03-17", "K"),
("94081265379", "Patryk", "Ostrowski", "1994-08-12", "M"),
("93060393849", "Karolina", "Baran", "1993-06-03", "K"),
("90052491895", "Jakub", "Szulc", "1990-05-24", "M"),
("96011273346", "Paulina", "Włodarczyk", "1996-01-12", "K"),
("99082898469", "Mateusz", "Chmielewski", "1999-08-28", "M"),
("91050821969", "Ewelina", "Borkowska", "1991-05-08", "K"),
("95040334912", "Dariusz", "Sokołowski", "1995-04-03", "M"),
("98070141424", "Izabela", "Szczepańska", "1998-07-01", "K"),
("96032435143", "Artur", "Sawicki", "1996-03-24", "M"),
("91030219823", "Agnieszka", "Kucharska", "1991-03-02", "K"),
("98030447397", "Marcin", "Lis", "1998-03-04", "M"),
("92122491837", "Edyta", "Maciejewska", "1992-12-24", "K"),
("95011717449", "Bartłomiej", "Kubiak", "1995-01-17", "M"),
("98082088562", "Justyna", "Wilk", "1998-08-20", "K"),
("93072016617", "Adrian", "Wysocki", "1993-07-20", "M"),
("91032717619", "Klaudia", "Kaźmierczak", "1991-03-27", "K"),
("94093092653", "Radosław", "Czarnecki", "1994-09-30", "M"),
("91102544116", "Aneta", "Andrzejewska", "1991-10-25", "K"),
("93102317912", "Mariusz", "Malinowski", "1993-10-23", "M"),
("96100293475", "Renata", "Jaworska", "1996-10-02", "K"),
("98122116679", "Kamil", "Głowacki", "1998-12-21", "M");

-- osoby w wieku co najmniej 60 lat
INSERT INTO Ludzie (PESEL, imie, nazwisko, data_urodzenia, plec) VALUES
("59051417482", "Zbigniew", "Stępień", "1960-01-01", "M"),
("56051581599", "Helena", "Kwiatkowska", "1959-02-02", "K"),
("50071829279", "Janusz", "Wróbel", "1958-03-03", "M"),
("52101913383", "Barbara", "Górska", "1957-04-04", "K"),
("54030592833", "Andrzej", "Król", "1956-05-05", "M");
```

Tabelę zawody uzupełnij zawodami - polityk, nauczyciel,
lekarz, informatyk wraz z odpowiednimi widełkami pensji. 

```sql
-- bad zawod (pensja_min > pensja_max)
INSERT INTO Zawody (zawod_id, nazwa, pensja_min, pensja_max) VALUES
(1, "Polityk", 10000, 1000);

-- ERROR 4025 (23000): CONSTRAINT `Zawody.pensja_max` failed for `db2024`.`Zawody`

--
INSERT INTO Zawody (zawod_id, nazwa, pensja_min, pensja_max) VALUES
(1, "Polityk", 1000, 10000),
(2, "Nauczyciel", 2000, 3000),
(3, "Lekarz", 10000, 28000),
(4, "Informatyk", 6000, 35000);
```

Następnie, z wykorzystaniem kursora na tabeli Ludzie, przypisz każdej pełnoletniej osobie zawód (wraz z odpowiednią pensją) i uzupełnij tabelę Pracownicy. (Uwaga: zadbaj o to, aby żaden lekarz płci męskiej nie był starszy niż 65 lat, a żaden lekarz płci żeńskiej nie był starszy niż 60 lat).
