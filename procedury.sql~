DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `dodajProjekt`(
	IN PrzedmiotId int(11),
	IN Temat varchar(100),
	IN Opis varchar(1048),
	IN Miejsca int(11),
	In Wolne int(11))
BEGIN
INSERT INTO `zapisy`.`temat` (`przedmiot_id`, `temat`, `opis`, `miejsca`, `wolne_miejsca`) VALUES (PrzedmiotId, Temat, Opis, Miejsca, Wolne);
END$$
DELIMITER ;


DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `dodajTermin`(
	IN PrzedmiotId int(11),
	IN Dzien varchar(45),
	IN Godzina_od varchar(45),
	IN Godzina_do varchar(45),
	IN Miejsca int(11),
	IN Sala_id int(11)
	)
BEGIN
INSERT INTO `zapisy`.`termin` (`przedmiot_id`, `dzien`, `godzina_od`, `godzina_do`, `miejsca`, `sala_id`) VALUES (PrzedmiotId, Dzien, Godzina_od, Godzina_do, Miejsca, Sala_id);
END$$
DELIMITER ;

-- --------------------------------------------------------------------------------
-- Funkcja zwracająca id projektu studenta o id studentId z przedmiotu przedmiotId
-- --------------------------------------------------------------------------------
DELIMITER $$

CREATE FUNCTION `szukajProjektuStudentaWPrzedmiot` (
	studentId int(11),
	przedmiotId int(11))
RETURNS INTEGER
BEGIN

  DECLARE idProjektu int(11);
  SET idProjektu = 0;

	SELECT id_temat INTO idProjektu 
		FROM zapisy.student_temat 
		INNER JOIN zapisy.temat 
		ON zapisy.student_temat.id_temat=zapisy.temat.id
		WHERE id_student = studentId and przedmiot_id = przedmiotId;

  RETURN id_projektu;
END


DELIMITER $$

CREATE PROCEDURE `szukajProjektuStudenta` (
	studentId int(11),
	przedmiotId int(11))
BEGIN

	SELECT id_temat 
		FROM zapisy.student_temat 
		INNER JOIN zapisy.temat 
		ON zapisy.student_temat.id_temat=zapisy.temat.id
		WHERE id_student = studentId and przedmiot_id = przedmiotId;
END


DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `zapiszProjekt`(
	IN StudentId int(11),
	IN TematId int(11)
	)
BEGIN
INSERT INTO `zapisy`.`student_temat` (`id_student`, `id_temat`) VALUES (StudentId, TematId);
END$$
DELIMITER ;


USE `zapisy`;
DROP procedure IF EXISTS `zapiszTermin`;

DELIMITER $$
USE `zapisy`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `zapiszTermin`(
	IN StudentId int(11),
	IN TerminId int(11)
	)
BEGIN
INSERT INTO `zapisy`.`student_termin` (`id_student`, `id_termin`) VALUES (StudentId, TerminId);
END$$

DELIMITER ;


USE `zapisy`;
DROP procedure IF EXISTS `dodajProwadzacego`;

DELIMITER $$
USE `zapisy`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `dodajProwadzacego`(
	IN Email varchar(45),
	IN Haslo varchar(45),
	IN Imie varchar(45),
	IN Nazwisko varchar(45)
	)
BEGIN
INSERT INTO `zapisy`.`prowadzacy` (`email`, `haslo`,`imie`,`nazwisko`) VALUES (Email, Haslo, Imie, Nazwisko);
END$$

DELIMITER ;


-- --------------------------------------------------------------------------------
-- Routine DDL
-- Note: comments before and after the routine body will not be stored by the server
-- --------------------------------------------------------------------------------
DELIMITER $$

CREATE DEFINER=`root`@`localhost` PROCEDURE `dodajStudenta`(
	IN `Index` varchar(45),
	IN Imie varchar(45),
	IN Nazwisko varchar(45)
	)
BEGIN
INSERT INTO `zapisy`.`student` (`index`,`imie`,`nazwisko`) VALUES (`Index`, Imie, Nazwisko);
END

-- --------------------------------------------------------------------------------
-- Routine DDL
-- Note: comments before and after the routine body will not be stored by the server
-- --------------------------------------------------------------------------------
DELIMITER $$

CREATE DEFINER=`root`@`localhost` PROCEDURE `dodajStudentaDoPrzedmiotu`(
	IN StudentId varchar(45),
	IN PrzedmiotId varchar(45)
	)
BEGIN
INSERT INTO `zapisy`.`student` (`student_id`,`przedmiot_id`) VALUES (StudentId, PrzedmiotId);
END

DELIMITER $$
CREATE DEFINER=`root`@`localhost` PROCEDURE `dodajPrzedmiot`(
	IN Nazwa varchar(45),
	IN Typ int(11)
	)
BEGIN
INSERT INTO `zapisy`.`przedmiot` (`nazwa`,`typ`) VALUES (Nazwa, Typ);
END$$
DELIMITER ;

-- --------------------------------------------------------------------------------
-- Routine DDL
-- Note: comments before and after the routine body will not be stored by the server
-- --------------------------------------------------------------------------------
DELIMITER $$

CREATE PROCEDURE `wypiszZProjektu` (
	IN StudentId INT(11),
	IN ProjektId INT(11)
)
BEGIN
DELETE FROM student_temat WHERE `id_student`=StudentId AND `id_temat`=ProjektId;
UPDATE temat SET wolne_miejsca = wolne_miejsca + 1 WHERE `id`=ProjektId; 
END

-- --------------------------------------------------------------------------------
-- Routine DDL
-- Note: comments before and after the routine body will not be stored by the server
-- --------------------------------------------------------------------------------
DELIMITER $$

CREATE DEFINER=`root`@`127.0.0.1` PROCEDURE `wypiszZTerminu`(
	IN StudentId INT(11),
	IN TerminId INT(11)
)
BEGIN
DELETE FROM student_termin WHERE `id_student`=StudentId AND `id_termin`=TerminId;
UPDATE termin SET miejsca = miejsca + 1 WHERE `id`=TerminId; 
END

DELIMITER $$

CREATE PROCEDURE `usunTemat` (
	IN tematId INT(11)
)
BEGIN
DELETE FROM student_temat WHERE id_temat=tematId;
DELETE FROM temat where id=tematId;
END


USE `zapisy`;
DROP procedure IF EXISTS `zapisy`.`usunTemat`;

DELIMITER $$
USE `zapisy`$$
CREATE DEFINER=`root`@`127.0.0.1` PROCEDURE `usunTermin`(
	IN terminId INT(11)
)
BEGIN
DELETE FROM student_termin WHERE id_termin=terminId;
DELETE FROM termin where id=terminId;
END$$

DELIMITER ;
;


-- --------------------------------------------------------------------------------
-- Routine DDL
-- Note: comments before and after the routine body will not be stored by the server
-- --------------------------------------------------------------------------------
DELIMITER $$

CREATE PROCEDURE `usunWszystkieTematyPrzedmiotu` (
	IN przedmiotId INT(11)
)
BEGIN
	DELETE FROM student_temat WHERE id_temat IN (
		SELECT id FROM temat where przedmiot_id=przedmiotId
	);
	DELETE FROM temat WHERE przedmiot_id=przedmiotId;
END


-- --------------------------------------------------------------------------------
-- Routine DDL
-- Note: comments before and after the routine body will not be stored by the server
-- --------------------------------------------------------------------------------
DELIMITER $$

CREATE DEFINER=`root`@`127.0.0.1` PROCEDURE `usunWszystkieTerminyPrzedmiotu`(
	IN przedmiotId INT(11)
)
BEGIN
	DELETE FROM student_termin WHERE id_termin IN (
		SELECT id FROM termin where przedmiot_id=przedmiotId
	);
	DELETE FROM termin WHERE przedmiot_id=przedmiotId;
END
