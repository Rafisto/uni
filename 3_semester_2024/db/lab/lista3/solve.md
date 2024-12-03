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
- Zawody (zawod_id: int, nazwa: varchar(50), pensja_min: float,
pensja_ max: float)
- Pracownicy (PESEL: char(11), zawod_id: int, pensja: float)

Tworzę bazę `db2024` oraz tabele `Ludzie`, `Zawody` and `Pracownicy`:

```sql
USE db2024;

-- ValidatePesel function
DELIMITER $$
CREATE FUNCTION IsValidPesel(pesel CHAR(11))
RETURNS BOOLEAN
DETERMINISTIC
BEGIN
-- Check if the input is exactly 11 digits
IF LENGTH(pesel) != 11 OR pesel NOT REGEXP '^\[0-9\]{11}$' THEN
RETURN FALSE;
END IF;
-- Define weights for checksum calculation
DECLARE weights CHAR(10) DEFAULT '1379137913';
DECLARE checksum INT DEFAULT 0;
-- Calculate checksum
DECLARE i INT DEFAULT 1;
WHILE i <= 10 DO
    SET checksum = checksum + (CAST(SUBSTRING(pesel, i, 1) AS UNSIGNED) * CAST(SUBSTRING(weights, i, 1) AS UNSIGNED));
    SET i = i + 1;
END WHILE;
SET checksum = (10 - (checksum MOD 10)) MOD 10;
-- Compare calculated checksum with the last digit of PESEL
IF checksum = CAST(SUBSTRING(pesel, 11, 1) AS UNSIGNED) THEN
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


```




Tabelę zawody uzupełnij zawodami - polityk, nauczyciel,
lekarz, informatyk wraz z odpowiednimi widełkami pensji. Nast˛epnie, z wy-
korzystaniem kursora na tabeli Ludzie, przypisz ka˙zdej pełnoletniej osobie
1https://www.gov.pl/web/gov/czym-jest-numer-pesel
zawód (wraz z odpowiedni ˛a pensj ˛a) i uzupełnij tabel˛e Pracownicy (Uwaga:
zadbaj o to, aby ˙zaden lekarz płci m˛eskiej nie był starszy ni˙z 65 lat a ˙zaden
lekarz płci ˙ze´nskiej nie był starszy ni˙z 60 lat).