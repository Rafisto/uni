USE db2024;

-- ValidatePesel function
DELIMITER $$
CREATE FUNCTION ValidatePESEL(PESEL CHAR(11))
RETURNS INT
DETERMINISTIC
BEGIN
DECLARE weight INT DEFAULT 2;
DECLARE sum INT DEFAULT 0;
DECLARE check_digit INT;
DECLARE isValid INT DEFAULT 1;

-- Check if PESEL has 11 digits
IF LENGTH(PESEL) != 11 OR PESEL NOT REGEXP '^[0-9]{11}$' THEN
    SET isValid = 0;
ELSE
    -- Calculate the sum of weighted digits
    WHILE weight <= 11 DO
        SET sum = sum + POWER(10, 11 - weight) * SUBSTRING(PESEL, weight, 1);
        SET weight = weight + 1;
    END WHILE;

    -- Calculate the check digit
    SET check_digit = MOD(sum, 10);

    -- Check if the calculated check digit matches the last digit of PESEL
    IF check_digit != SUBSTRING(PESEL, 11, 1) THEN
        SET isValid = 0;
    END IF;
END IF;
RETURN isValid;

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