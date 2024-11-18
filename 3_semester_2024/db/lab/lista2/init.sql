CREATE DATABASE aparaty;
CREATE USER '123456'@'%' IDENTIFIED BY 'kowalski56';

GRANT SELECT, INSERT, UPDATE ON aparaty.* TO '123456'@'%';
FLUSH PRIVILEGES;

USE aparaty;

CREATE TABLE Matryca (
    ID INT PRIMARY KEY AUTO_INCREMENT,
    przekatna DECIMAL(4,2) CHECK (przekatna >= 0), -- 4 cyfry, 2 po przecinku
    rozdzielczosc DECIMAL(3,1) CHECK (rozdzielczosc >= 0), -- 3 cyfry, 1 po przecinku
    typ VARCHAR(10)
) AUTO_INCREMENT = 100;

CREATE TABLE Obiektyw (
    ID INT PRIMARY KEY AUTO_INCREMENT,
    model VARCHAR(30),
    minPrzeslona FLOAT CHECK (minPrzeslona >= 0),
    maxPrzeslona FLOAT CHECK (maxPrzeslona > minPrzeslona),
    CONSTRAINT check_min_max CHECK (minPrzeslona < maxPrzeslona)
) AUTO_INCREMENT = 1;

CREATE TABLE Producent (
    ID INT PRIMARY KEY AUTO_INCREMENT,
    nazwa VARCHAR(50) NOT NULL,
    kraj VARCHAR(20) DEFAULT 'nieznany',
    adresKorespondencyjny VARCHAR(100) DEFAULT 'nieznany'
) AUTO_INCREMENT = 1;

CREATE TABLE Aparat (
    model VARCHAR(30) PRIMARY KEY,
    producent INT,
    matryca INT,
    obiektyw INT,
    waga FLOAT,
    typ ENUM('kompaktowy', 'lustrzanka', 'profesjonalny', 'inny'),
    FOREIGN KEY (producent) REFERENCES Producent(ID),
    FOREIGN KEY (matryca) REFERENCES Matryca(ID),
    FOREIGN KEY (obiektyw) REFERENCES Obiektyw(ID)
);

INSERT INTO Producent(nazwa,kraj) VALUES ('Canon', 'Japonia');
INSERT INTO Producent(nazwa,kraj) VALUES ('Nikon', 'Japonia');
INSERT INTO Producent(nazwa,kraj) VALUES ('Sony', 'Japonia');
INSERT INTO Producent(nazwa,kraj) VALUES ('Panasonic', 'Japonia');
INSERT INTO Producent(nazwa,kraj) VALUES ('Olympus', 'Japonia');
INSERT INTO Producent(nazwa,kraj) VALUES ('Fujifilm', 'Japonia');
INSERT INTO Producent(nazwa,kraj) VALUES ('Huawei', 'Chiny');
INSERT INTO Producent(nazwa,kraj) VALUES ('Xiaomi', 'Chiny');
INSERT INTO Producent(nazwa,kraj) VALUES ('DJI', 'Chiny');
INSERT INTO Producent(nazwa,kraj) VALUES ('YI Technology', 'Chiny');
INSERT INTO Producent(nazwa,kraj) VALUES ('Zhiyun Technology', 'Chiny');
INSERT INTO Producent(nazwa,kraj) VALUES ('GoPro', 'USA');
INSERT INTO Producent(nazwa,kraj) VALUES ('Kodak', 'USA');
INSERT INTO Producent(nazwa,kraj) VALUES ('Leica', 'Niemcy');
INSERT INTO Producent(nazwa,kraj) VALUES ('Hasselblad', 'Szwecja');

INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (1.1, 20.1, 'CMOS');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (1.2, 18.3, 'CCD');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (1.5, 22.0, 'CMOS');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (1.3, 19.7, 'CCD');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (1.4, 21.5, 'CMOS');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (1.6, 23.2, 'CCD');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (1.7, 24.0, 'CMOS');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (1.8, 25.5, 'CCD');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (2.0, 26.8, 'CMOS');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (1.9, 28.3, 'CCD');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (2.1, 29.0, 'CMOS');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (2.2, 30.5, 'LIDAR');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (2.3, 32.1, 'CMOS');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (2.4, 34.0, 'CCD');
INSERT INTO Matryca(przekatna, rozdzielczosc, typ) VALUES (2.5, 36.0, 'CMOS');

INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Canon EF 50mm f/1.8 STM', 1.8, 22);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Nikon AF-S 50mm f/1.8G', 1.8, 16);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Sony FE 24-70mm f/2.8 GM', 2.8, 22);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Tamron 70-200mm f/2.8 G2', 2.8, 22);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Sigma 35mm f/1.4 DG HSM', 1.4, 16);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Canon RF 85mm f/1.2L USM', 1.2, 16);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Nikon Z 24-70mm f/2.8 S', 2.8, 22);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Fujifilm XF 23mm f/1.4 R', 1.4, 16);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Olympus M.Zuiko 8 PRO', 2.8, 22);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Leica Summilux-M 50mmH', 1.4, 16);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Panasonic Lumix G 25mm', 1.7, 22);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Tokina AT-X 11-16mm', 2.8, 22);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Samyang 14mm f/2.8', 2.8, 22);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Zeiss Loxia 35mm f/2', 2, 22);
INSERT INTO Obiektyw(model, minPrzeslona, maxPrzeslona) VALUES ('Voigtlander 35mm', 1.4, 16);

INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Canon EOS 5D Mark II', 1, 100, 1, 800, 'lustrzanka');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Canon EOS 5D Mark III', 1, 101, 1, 800, 'lustrzanka');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Canon EOS 5D Mark IV', 1, 102, 1, 800, 'lustrzanka');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Canon EOS 5D Mark V', 1, 103, 1, 800, 'lustrzanka');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Nikon D850', 2, 101, 2, 915, 'lustrzanka');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Sony Alpha 7R IV', 3, 102, 3, 665, 'profesjonalny');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Panasonic Lumix GH5', 4, 103, 4, 725, 'profesjonalny');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Olympus OM-D E-M1 Mark III', 5, 104, 5, 500, 'profesjonalny');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Fujifilm X-T4', 6, 105, 6, 600, 'profesjonalny');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Huawei P40 Pro', 7, 106, 7, 209, 'kompaktowy');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Xiaomi Mi 10 Ultra', 8, 107, 8, 220, 'kompaktowy');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('DJI Osmo Pocket', 9, 108, 9, 116, 'kompaktowy');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('YI 4K Action Camera', 10, 109, 10, 94, 'kompaktowy');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Zhiyun Crane M2', 11, 110, 11, 500, 'inny');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('GoPro HERO10 Black', 12, 111, 12, 153, 'kompaktowy');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Kodak PIXPRO SP360 4K', 13, 112, 13, 196, 'kompaktowy');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Leica M10-R', 14, 113, 14, 660, 'lustrzanka');
INSERT INTO Aparat(model, producent, matryca, obiektyw, waga, typ) VALUES ('Hasselblad X1D II 50C', 15, 114, 15, 725, 'profesjonalny');