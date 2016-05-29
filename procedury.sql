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

