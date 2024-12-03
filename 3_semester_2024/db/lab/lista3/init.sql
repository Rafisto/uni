/*M!999999\- enable the sandbox mode */ 
-- MariaDB dump 10.19-11.5.2-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: db2024
-- ------------------------------------------------------
-- Server version	11.5.2-MariaDB-ubu2404

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*M!100616 SET @OLD_NOTE_VERBOSITY=@@NOTE_VERBOSITY, NOTE_VERBOSITY=0 */;

--
-- Table structure for table `Ludzie`
--

DROP TABLE IF EXISTS `Ludzie`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Ludzie` (
  `PESEL` char(11) NOT NULL,
  `imie` varchar(30) NOT NULL,
  `nazwisko` varchar(30) NOT NULL,
  `data_urodzenia` date NOT NULL,
  `plec` enum('K','M') NOT NULL,
  PRIMARY KEY (`PESEL`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Ludzie`
--

LOCK TABLES `Ludzie` WRITE;
/*!40000 ALTER TABLE `Ludzie` DISABLE KEYS */;
INSERT INTO `Ludzie` VALUES
('20210665727','Piotr','Wiśniewski','2020-03-03','M'),
('20240988645','Anna','Nowak','2020-02-02','K'),
('20241092938','Maria','Lewandowska','2020-05-05','K'),
('20250352229','Jan','Kowalski','2020-01-01','M'),
('20290314391','Zofia','Dąbrowska','2020-04-04','K'),
('50071829279','Janusz','Wróbel','1958-03-03','M'),
('52101913383','Barbara','Górska','1957-04-04','K'),
('54030592833','Andrzej','Król','1956-05-05','M'),
('56051581599','Helena','Kwiatkowska','1959-02-02','K'),
('59051417482','Zbigniew','Stępień','1960-01-01','M'),
('90012218753','Anna','Wójcik','1990-01-22','K'),
('90052491895','Jakub','Szulc','1990-05-24','M'),
('90052587741','Magdalena','Mazur','1990-05-25','K'),
('90101783542','Wojciech','Adamczyk','1990-10-17','M'),
('90102676254','Rafał','Krawczyk','1990-10-26','M'),
('90110243295','Krzysztof','Michalski','1990-11-02','M'),
('90112354171','Joanna','Kozłowska','1990-11-23','K'),
('91030219823','Agnieszka','Kucharska','1991-03-02','K'),
('91032717619','Klaudia','Kaźmierczak','1991-03-27','K'),
('91050821969','Ewelina','Borkowska','1991-05-08','K'),
('91091646426','Ewa','Kowalska','1991-09-16','K'),
('91102544116','Aneta','Andrzejewska','1991-10-25','K'),
('92072765217','Dorota','Piotrowska','1992-07-27','K'),
('92112662672','Marek','Kowalczyk','1992-11-26','M'),
('92122491837','Edyta','Maciejewska','1992-12-24','K'),
('93031773427','Natalia','Sikora','1993-03-17','K'),
('93060393849','Karolina','Baran','1993-06-03','K'),
('93072016617','Adrian','Wysocki','1993-07-20','M'),
('93102317912','Mariusz','Malinowski','1993-10-23','M'),
('94052393539','Beata','Nowicka','1994-05-23','K'),
('94062483824','Sebastian','Zawadzki','1994-06-24','M'),
('94070719854','Grzegorz','Grabowski','1994-07-07','M'),
('94081265379','Patryk','Ostrowski','1994-08-12','M'),
('94093092653','Radosław','Czarnecki','1994-09-30','M'),
('95011717449','Bartłomiej','Kubiak','1995-01-17','M'),
('95040334912','Dariusz','Sokołowski','1995-04-03','M'),
('95071995571','Sylwia','Pawlak','1995-07-19','K'),
('95122189245','Alicja','Dudek','1995-12-21','K'),
('96011273346','Paulina','Włodarczyk','1996-01-12','K'),
('96032435143','Artur','Sawicki','1996-03-24','M'),
('96081447663','Paweł','Szymański','1996-08-14','M'),
('96100293475','Renata','Jaworska','1996-10-02','K'),
('96110957767','Piotr','Wiśniewski','1996-11-09','M'),
('96123193569','Katarzyna','Kamińska','1996-12-31','K'),
('97041719691','Adam','Nowak','1997-04-17','M'),
('97071114468','Łukasz','Dąbrowski','1997-07-11','M'),
('98012855439','Monika','Woźniak','1998-01-28','K'),
('98030447397','Marcin','Lis','1998-03-04','M'),
('98041188535','Michał','Jankowski','1998-04-11','M'),
('98070141424','Izabela','Szczepańska','1998-07-01','K'),
('98082088562','Justyna','Wilk','1998-08-20','K'),
('98112451423','Agnieszka','Zielińska','1998-11-24','K'),
('98122116679','Kamil','Głowacki','1998-12-21','M'),
('99041958393','Tomasz','Lewandowski','1999-04-19','M'),
('99082898469','Mateusz','Chmielewski','1999-08-28','M');
/*!40000 ALTER TABLE `Ludzie` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb3 */ ;
/*!50003 SET character_set_results = utf8mb3 */ ;
/*!50003 SET collation_connection  = utf8mb3_uca1400_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER ValidatePESELTrigger
BEFORE INSERT ON Ludzie
FOR EACH ROW
BEGIN
    DECLARE isValid INT;
    SET isValid = ValidatePESEL(NEW.PESEL);
    IF isValid = FALSE THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Invalid PESEL';
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `Pracownicy`
--

DROP TABLE IF EXISTS `Pracownicy`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Pracownicy` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `PESEL` char(11) NOT NULL,
  `zawod_id` int(11) DEFAULT NULL,
  `pensja` float DEFAULT NULL CHECK (`pensja` >= 0),
  PRIMARY KEY (`id`,`PESEL`),
  KEY `PESEL` (`PESEL`),
  KEY `zawod_id` (`zawod_id`),
  CONSTRAINT `Pracownicy_ibfk_1` FOREIGN KEY (`PESEL`) REFERENCES `Ludzie` (`PESEL`),
  CONSTRAINT `Pracownicy_ibfk_2` FOREIGN KEY (`zawod_id`) REFERENCES `Zawody` (`zawod_id`)
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Pracownicy`
--

LOCK TABLES `Pracownicy` WRITE;
/*!40000 ALTER TABLE `Pracownicy` DISABLE KEYS */;
INSERT INTO `Pracownicy` VALUES
(1,'50071829279',2,2734.53),
(2,'52101913383',1,7655.92),
(3,'54030592833',4,15905.1),
(4,'56051581599',1,1747.45),
(5,'59051417482',1,5505.78),
(6,'90012218753',4,13712.5),
(7,'90052491895',2,2619.11),
(8,'90052587741',4,22458.1),
(9,'90101783542',4,24864.8),
(10,'90102676254',2,2595.96),
(11,'90110243295',2,2966.2),
(12,'90112354171',4,15631),
(13,'91030219823',1,1585.6),
(14,'91032717619',1,3444.34),
(15,'91050821969',2,2788.92),
(16,'91091646426',3,21815.8),
(17,'91102544116',1,5813.05),
(18,'92072765217',1,3632.46),
(19,'92112662672',2,2479),
(20,'92122491837',3,18093.6),
(21,'93031773427',1,8476.65),
(22,'93060393849',3,11352),
(23,'93072016617',1,9248.93),
(24,'93102317912',3,21805.7),
(25,'94052393539',2,2694.23),
(26,'94062483824',3,21033.4),
(27,'94070719854',3,17627.5),
(28,'94081265379',1,1736.19),
(29,'94093092653',2,2682.76),
(30,'95011717449',3,13502.6),
(31,'95040334912',4,9128.45),
(32,'95071995571',2,2834.4),
(33,'95122189245',4,21226.7),
(34,'96011273346',4,26297.9),
(35,'96032435143',4,29361.3),
(36,'96081447663',1,2074.79),
(37,'96100293475',3,17123),
(38,'96110957767',1,7012.85),
(39,'96123193569',4,14112.6),
(40,'97041719691',3,14988.9),
(41,'97071114468',3,25088.3),
(42,'98012855439',1,1442.8),
(43,'98030447397',3,25819.1),
(44,'98041188535',2,2334.68),
(45,'98070141424',4,8869.92),
(46,'98082088562',1,6778.22),
(47,'98112451423',4,33218.4),
(48,'98122116679',1,4346.74),
(49,'99041958393',1,4802.74),
(50,'99082898469',3,25557.2);
/*!40000 ALTER TABLE `Pracownicy` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb3 */ ;
/*!50003 SET character_set_results = utf8mb3 */ ;
/*!50003 SET collation_connection  = utf8mb3_uca1400_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER ValidatePensjaTrigger
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
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `Zawody`
--

DROP TABLE IF EXISTS `Zawody`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Zawody` (
  `zawod_id` int(11) NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(50) DEFAULT NULL,
  `pensja_min` float DEFAULT NULL CHECK (`pensja_min` >= 0),
  `pensja_max` float DEFAULT NULL CHECK (`pensja_max` > `pensja_min`),
  PRIMARY KEY (`zawod_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Zawody`
--

LOCK TABLES `Zawody` WRITE;
/*!40000 ALTER TABLE `Zawody` DISABLE KEYS */;
INSERT INTO `Zawody` VALUES
(1,'Polityk',1000,10000),
(2,'Nauczyciel',2000,3000),
(3,'Lekarz',10000,28000),
(4,'Informatyk',6000,35000);
/*!40000 ALTER TABLE `Zawody` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'db2024'
--
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
/*!50003 DROP FUNCTION IF EXISTS `ValidatePESEL` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb3 */ ;
/*!50003 SET character_set_results = utf8mb3 */ ;
/*!50003 SET collation_connection  = utf8mb3_uca1400_ai_ci */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` FUNCTION `ValidatePESEL`(pesel CHAR(11)) RETURNS tinyint(1)
    DETERMINISTIC
BEGIN
    
    IF LENGTH(pesel) != 11 OR pesel NOT REGEXP '^[0-9]{11}$' THEN
        RETURN FALSE;
    END IF;

    
    SET @weights = '1379137913';
    SET @checksum = 0;

    
    SET @i = 1;
    WHILE @i <= 10 DO
        SET @checksum = @checksum +
            (CAST(SUBSTRING(pesel, @i, 1) AS UNSIGNED) *
             CAST(SUBSTRING(@weights, @i, 1) AS UNSIGNED));
        SET @i = @i + 1;
    END WHILE;

    SET @checksum = (10 - (@checksum MOD 10)) MOD 10;

    
    IF @checksum = CAST(SUBSTRING(pesel, 11, 1) AS UNSIGNED) THEN
        RETURN TRUE;
    ELSE
        RETURN FALSE;
    END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
/*!50003 DROP PROCEDURE IF EXISTS `AddEmployees` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb3 */ ;
/*!50003 SET character_set_results = utf8mb3 */ ;
/*!50003 SET collation_connection  = utf8mb3_uca1400_ai_ci */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `AddEmployees`()
BEGIN
    
    DECLARE done INT DEFAULT FALSE;
    DECLARE t_pesel CHAR(11);
    DECLARE t_birthdate DATE;
    DECLARE t_gender ENUM('K', 'M');
    DECLARE t_age INT;
    DECLARE random_profession_id INT;
    DECLARE min_salary FLOAT;
    DECLARE max_salary FLOAT;
    DECLARE rnd_salary FLOAT;

    DECLARE ludzie_cursor CURSOR FOR
        SELECT PESEL, data_urodzenia, plec
        FROM Ludzie
        WHERE DATEDIFF(CURDATE(), data_urodzenia) / 365.25 >= 18;

    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

    OPEN ludzie_cursor;

    ludzie_loop: LOOP
        IF done THEN
            LEAVE ludzie_loop;
        END IF;

        
        FETCH ludzie_cursor INTO t_pesel, t_birthdate, t_gender;

        
        SET t_age = FLOOR(DATEDIFF(CURDATE(), t_birthdate) / 365.25);

        
        REPEAT
            SELECT zawod_id, pensja_min, pensja_max
            INTO random_profession_id, min_salary, max_salary
            FROM Zawody
            ORDER BY RAND()
            LIMIT 1;

            
            IF (random_profession_id = (SELECT zawod_id FROM Zawody WHERE nazwa = 'Lekarz')) THEN
                IF (t_gender = 'M' AND t_age > 65) OR (t_gender = 'K' AND t_age > 60) THEN
                    SET random_profession_id = NULL;
                END IF;
            END IF;
        UNTIL random_profession_id IS NOT NULL END REPEAT;

        
        SET rnd_salary = min_salary + RAND() * (max_salary - min_salary);

        
        IF NOT EXISTS (
            SELECT 1 FROM Pracownicy 
            WHERE PESEL = t_pesel AND zawod_id = random_profession_id
        ) THEN
            INSERT INTO Pracownicy (PESEL, zawod_id, pensja)
            VALUES (t_pesel, random_profession_id, rnd_salary);
        END IF;

    END LOOP;

    
    CLOSE ludzie_cursor;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*M!100616 SET NOTE_VERBOSITY=@OLD_NOTE_VERBOSITY */;

-- Dump completed on 2024-12-03 20:41:44
