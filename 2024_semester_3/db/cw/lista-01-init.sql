CREATE TABLE Firma (
    Nazwa VARCHAR(30) PRIMARY KEY,
    Adres VARCHAR(80),
    Data_zalozenia DATE,
    Imie_prezesa VARCHAR(30),
    Nazwisko_prezesa VARCHAR(30),
    Pesel_prezesa CHAR(11)
);

CREATE TABLE Pracownicy (
    Id INT PRIMARY KEY AUTO_INCREMENT,
    Imie VARCHAR(20),
    Nazwisko VARCHAR(30),
    Pesel CHAR(11)
);


CREATE TABLE Zatrudnienie (
    Id_pracownika INT PRIMARY KEY AUTO_INCREMENT,
    Nazwa_firmy VARCHAR(30),
    Data_zatrudnienia DATE,
    Data_zwolnienia DATE,
    Wynagrodzenie_brutto INT,
    FOREIGN KEY (Id_pracownika) REFERENCES Pracownicy(Id),
    FOREIGN KEY (Nazwa_firmy) REFERENCES Firma(Nazwa)
);

CREATE TABLE Obroty (
    Nazwa_firmy VARCHAR(30),
    Rok INT,
    Miesiac INT,
    Przychod INT,
    Wydatki INT,
    FOREIGN KEY (Nazwa_firmy) REFERENCES Firma(Nazwa)
);

INSERT INTO Firma (Nazwa, Adres, Data_zalozenia, Imie_prezesa, Nazwisko_prezesa, Pesel_prezesa) 
VALUES 
('TechCorp', '123 Innovation Ave, Warsaw', '2010-05-15', 'Jan', 'Kowalski', '12345678901'),
('UltraCorp', '123 Innovation Ave, Warsaw', '1999-05-10', 'Jan', 'Kowalski', '12345678901'),
('EcoSolutions', '456 Green St, Krakow', '2015-08-22', 'Anna', 'Nowak', '98765432109'),
('MediCare', '789 Health Blvd, Gdansk', '2008-03-11', 'Piotr', 'Zielinski', '45612378900');

INSERT INTO Pracownicy (Imie, Nazwisko, Pesel) 
VALUES 
('Mateusz', 'Kaminski', '11122233344'),
('Magda', 'Wisniewska', '55566677788'),
('Tomasz', 'Lewandowski', '99988877766');

INSERT INTO Obroty (Nazwa_firmy, Rok, Miesiac, Przychod, Wydatki) 
VALUES 
('TechCorp', 2023, 1, 500000, 200000),
('TechCorp', 2023, 2, 550000, 210000),
('EcoSolutions', 2023, 1, 300000, 150000),
('EcoSolutions', 2023, 2, 320000, 160000),
('MediCare', 2023, 1, 700000, 250000),
('MediCare', 2023, 2, 730000, 260000);

INSERT INTO Zatrudnienie (Id_pracownika, Nazwa_firmy, Data_zatrudnienia, Data_zwolnienia, Wynagrodzenie_brutto) 
VALUES 
(1, 'TechCorp', '2020-06-01', NULL, 120000),
(2, 'EcoSolutions', '2019-04-15', '2023-07-30', 110000),
(3, 'MediCare', '2021-09-20', NULL, 130000);
