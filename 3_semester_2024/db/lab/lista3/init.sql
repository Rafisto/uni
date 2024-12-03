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
    IF isValid = 0 THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Invalid PESEL number';
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