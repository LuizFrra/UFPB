-- MySQL dump 10.13  Distrib 5.7.24, for Linux (x86_64)
--
-- Host: localhost    Database: SocialNet
-- ------------------------------------------------------
-- Server version	5.7.24-0ubuntu0.18.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Comentario`
--

DROP TABLE IF EXISTS `Comentario`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Comentario` (
  `ComentarioID` int(11) NOT NULL AUTO_INCREMENT,
  `UserID` int(11) NOT NULL,
  `PublicacaoID` int(11) NOT NULL,
  `Texto` varchar(500) NOT NULL,
  PRIMARY KEY (`ComentarioID`),
  KEY `PublicacaoID` (`PublicacaoID`),
  KEY `UserID` (`UserID`),
  CONSTRAINT `Comentario_ibfk_1` FOREIGN KEY (`PublicacaoID`) REFERENCES `Publicacao` (`PublicacaoID`) ON DELETE CASCADE,
  CONSTRAINT `Comentario_ibfk_2` FOREIGN KEY (`UserID`) REFERENCES `Users` (`UserID`)
) ENGINE=InnoDB AUTO_INCREMENT=35 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Comentario`
--

LOCK TABLES `Comentario` WRITE;
/*!40000 ALTER TABLE `Comentario` DISABLE KEYS */;
INSERT INTO `Comentario` VALUES (3,5,9,'é muito bom'),(10,5,12,'oi'),(11,6,13,'parabens'),(12,6,12,'oi jonas '),(14,7,10,'bronze'),(15,7,12,'Gostaria de saber quando abre as matriculas'),(16,4,19,'concordo amigo'),(17,4,3,'Eu tambem estou'),(20,10,4,'lindo kkkk'),(22,10,12,'oi jonas'),(23,10,3,'eu tambem estou'),(24,10,3,'e vou dar 10 a voces'),(25,10,21,'sim, teremos.'),(26,10,30,'ATE AGORA OK'),(28,4,32,'OLAAAA'),(29,2,32,'ATE AGR OK'),(30,4,33,'OBAA o/'),(32,2,33,'ESTAMOS INDO BEM ?'),(34,10,36,'TA QUASE GAROTO');
/*!40000 ALTER TABLE `Comentario` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Grupo`
--

DROP TABLE IF EXISTS `Grupo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Grupo` (
  `GrupoID` int(11) NOT NULL AUTO_INCREMENT,
  `Nome` varchar(50) NOT NULL,
  `Visibilidade` int(11) DEFAULT '0',
  `Descricao` varchar(1000) DEFAULT NULL,
  `Foto` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`GrupoID`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Grupo`
--

LOCK TABLES `Grupo` WRITE;
/*!40000 ALTER TABLE `Grupo` DISABLE KEYS */;
INSERT INTO `Grupo` VALUES (1,'Ufpb',0,'Amigos da faculdade','~/images/201807011106_5.jpg'),(2,'SHANKS VIVE',1,'O SHANKS NAO  MORREU','~/images/201827011134_8.jpg'),(3,'Fã clube do Pepe',1,'Somente as pessoas q admiram Pepe','~/images/201841011118_4.png');
/*!40000 ALTER TABLE `Grupo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `GrupoAdmin`
--

DROP TABLE IF EXISTS `GrupoAdmin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `GrupoAdmin` (
  `GrupoID` int(11) NOT NULL,
  `UserID` int(11) NOT NULL,
  KEY `GrupoID` (`GrupoID`),
  KEY `UserID` (`UserID`),
  CONSTRAINT `GrupoAdmin_ibfk_1` FOREIGN KEY (`GrupoID`) REFERENCES `Grupo` (`GrupoID`) ON DELETE CASCADE,
  CONSTRAINT `GrupoAdmin_ibfk_2` FOREIGN KEY (`UserID`) REFERENCES `Users` (`UserID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `GrupoAdmin`
--

LOCK TABLES `GrupoAdmin` WRITE;
/*!40000 ALTER TABLE `GrupoAdmin` DISABLE KEYS */;
INSERT INTO `GrupoAdmin` VALUES (1,5),(2,8),(3,4);
/*!40000 ALTER TABLE `GrupoAdmin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `MuralGrupo`
--

DROP TABLE IF EXISTS `MuralGrupo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `MuralGrupo` (
  `GrupoID` int(11) NOT NULL,
  `PublicacaoID` int(11) NOT NULL,
  KEY `GrupoID` (`GrupoID`),
  KEY `PublicacaoID` (`PublicacaoID`),
  CONSTRAINT `MuralGrupo_ibfk_1` FOREIGN KEY (`GrupoID`) REFERENCES `Grupo` (`GrupoID`) ON DELETE CASCADE,
  CONSTRAINT `MuralGrupo_ibfk_2` FOREIGN KEY (`PublicacaoID`) REFERENCES `Publicacao` (`PublicacaoID`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `MuralGrupo`
--

LOCK TABLES `MuralGrupo` WRITE;
/*!40000 ALTER TABLE `MuralGrupo` DISABLE KEYS */;
INSERT INTO `MuralGrupo` VALUES (1,12),(2,19),(2,20),(1,27),(1,28),(1,35),(1,36),(1,37);
/*!40000 ALTER TABLE `MuralGrupo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `MuralUsers`
--

DROP TABLE IF EXISTS `MuralUsers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `MuralUsers` (
  `UserID` int(11) NOT NULL,
  `PublicacaoID` int(11) NOT NULL,
  KEY `PublicacaoID` (`PublicacaoID`),
  KEY `UserID` (`UserID`),
  CONSTRAINT `MuralUsers_ibfk_1` FOREIGN KEY (`PublicacaoID`) REFERENCES `Publicacao` (`PublicacaoID`) ON DELETE CASCADE,
  CONSTRAINT `MuralUsers_ibfk_2` FOREIGN KEY (`UserID`) REFERENCES `Users` (`UserID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `MuralUsers`
--

LOCK TABLES `MuralUsers` WRITE;
/*!40000 ALTER TABLE `MuralUsers` DISABLE KEYS */;
INSERT INTO `MuralUsers` VALUES (1,1),(1,2),(2,3),(2,4),(3,5),(2,6),(4,7),(5,8),(5,9),(5,10),(6,13),(7,14),(8,16),(8,17),(8,18),(10,21),(10,24),(2,25),(4,26),(10,29),(2,30),(2,32),(4,33);
/*!40000 ALTER TABLE `MuralUsers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Publicacao`
--

DROP TABLE IF EXISTS `Publicacao`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Publicacao` (
  `PublicacaoID` int(11) NOT NULL AUTO_INCREMENT,
  `UserID` int(11) NOT NULL,
  `Imagem` varchar(1024) DEFAULT NULL,
  `Texto` varchar(500) DEFAULT NULL,
  PRIMARY KEY (`PublicacaoID`),
  KEY `UserID` (`UserID`),
  CONSTRAINT `Publicacao_ibfk_1` FOREIGN KEY (`UserID`) REFERENCES `Users` (`UserID`)
) ENGINE=InnoDB AUTO_INCREMENT=38 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Publicacao`
--

LOCK TABLES `Publicacao` WRITE;
/*!40000 ALTER TABLE `Publicacao` DISABLE KEYS */;
INSERT INTO `Publicacao` VALUES (1,1,NULL,'eu estou me sentindo feliz'),(2,1,NULL,'esse periodo eu passo em apa'),(3,2,NULL,'eu estou feliz'),(4,2,'~/images/201858011101_2.png','esse é meu amigo pepe'),(5,3,NULL,'Eu gosto de comida\r\n'),(6,2,NULL,'Agora eu tenho um amigo chamado thales'),(7,4,NULL,'Estou sentindo saudades de casa'),(8,5,NULL,'Eu gosto de engenharia de computacao'),(9,5,NULL,'eu gosto de lol'),(10,5,NULL,'eu sou viciado em jogos'),(12,5,NULL,'Esse é um grupo para amigos da universidade'),(13,6,NULL,'Hoje eu fui apresentar bd e tirei 9'),(14,7,NULL,'Quintou!!!'),(16,8,NULL,'Estou me sentindo com raiva pq nao estou conseguindo terminar meu trabalho de arquitetura'),(17,8,NULL,'ferraz é um fuleiro. me deixou reprovar'),(18,8,NULL,'SHANKS ESTÁ VIVO'),(19,8,NULL,'So entre no grupo se vc concordar que shanks vive'),(20,4,NULL,'Eu gosto de one peace'),(21,2,NULL,'Professor teremos aula hoje ?'),(24,4,NULL,'Professor, terá aula hoje ?'),(25,10,NULL,'Luiz, teremos aula hoje.'),(26,10,NULL,'A apresentação do trabalho será hoje.'),(27,10,NULL,'Olá, a disciplina de banco de dados é a melhor do p5'),(28,10,NULL,'Eu estou animado para dar aula a voces'),(29,10,NULL,'hoje eu vou distribuir 10 para Gabriel e Luiz'),(30,2,NULL,'APRESENTANDO BD'),(32,10,NULL,'APRESENTANDO BDDDD'),(33,10,NULL,'APRESENTACAO BD ESTRUCT 3'),(35,2,NULL,'ULTIMA FASE'),(36,4,NULL,'ULTIMA FASE 2'),(37,4,NULL,'ULTIMA FASE 3');
/*!40000 ALTER TABLE `Publicacao` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Relacionamento`
--

DROP TABLE IF EXISTS `Relacionamento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Relacionamento` (
  `UserID1` int(11) NOT NULL,
  `UserID2` int(11) NOT NULL,
  `Status` int(11) NOT NULL,
  KEY `UserID2` (`UserID2`),
  KEY `UserID1` (`UserID1`),
  CONSTRAINT `Relacionamento_ibfk_1` FOREIGN KEY (`UserID1`) REFERENCES `Users` (`UserID`),
  CONSTRAINT `Relacionamento_ibfk_2` FOREIGN KEY (`UserID2`) REFERENCES `Users` (`UserID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Relacionamento`
--

LOCK TABLES `Relacionamento` WRITE;
/*!40000 ALTER TABLE `Relacionamento` DISABLE KEYS */;
INSERT INTO `Relacionamento` VALUES (3,2,3),(2,3,3),(5,4,3),(4,5,3),(6,5,4),(5,6,6),(7,6,1),(6,7,2),(7,5,3),(5,7,3),(4,8,3),(8,4,3),(8,5,3),(5,8,3),(2,10,3),(10,2,3),(2,5,3),(5,2,3),(10,5,3),(5,10,3),(10,4,3),(4,10,3),(2,4,4),(4,2,6);
/*!40000 ALTER TABLE `Relacionamento` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `RelacionamentoGU`
--

DROP TABLE IF EXISTS `RelacionamentoGU`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `RelacionamentoGU` (
  `GrupoID` int(11) NOT NULL,
  `UserID` int(11) NOT NULL,
  `Status` int(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`GrupoID`,`UserID`),
  KEY `UserID` (`UserID`),
  CONSTRAINT `RelacionamentoGU_ibfk_1` FOREIGN KEY (`GrupoID`) REFERENCES `Grupo` (`GrupoID`) ON DELETE CASCADE,
  CONSTRAINT `RelacionamentoGU_ibfk_2` FOREIGN KEY (`UserID`) REFERENCES `Users` (`UserID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `RelacionamentoGU`
--

LOCK TABLES `RelacionamentoGU` WRITE;
/*!40000 ALTER TABLE `RelacionamentoGU` DISABLE KEYS */;
INSERT INTO `RelacionamentoGU` VALUES (1,2,3),(1,4,2),(1,5,2),(1,6,2),(1,7,4),(1,9,2),(1,10,3),(2,4,3),(2,8,3),(3,2,1),(3,4,3);
/*!40000 ALTER TABLE `RelacionamentoGU` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Respostas`
--

DROP TABLE IF EXISTS `Respostas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Respostas` (
  `RespostaID` int(11) NOT NULL AUTO_INCREMENT,
  `UserID` int(11) NOT NULL,
  `ComentarioID` int(11) NOT NULL,
  `Texto` varchar(500) NOT NULL,
  PRIMARY KEY (`RespostaID`),
  KEY `UserID` (`UserID`),
  KEY `ComentarioID` (`ComentarioID`),
  CONSTRAINT `Respostas_ibfk_1` FOREIGN KEY (`UserID`) REFERENCES `Users` (`UserID`),
  CONSTRAINT `Respostas_ibfk_2` FOREIGN KEY (`ComentarioID`) REFERENCES `Comentario` (`ComentarioID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Respostas`
--

LOCK TABLES `Respostas` WRITE;
/*!40000 ALTER TABLE `Respostas` DISABLE KEYS */;
INSERT INTO `Respostas` VALUES (1,2,25,'obrigado'),(2,5,28,'BOA SORTE');
/*!40000 ALTER TABLE `Respostas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Users`
--

DROP TABLE IF EXISTS `Users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Users` (
  `UserID` int(11) NOT NULL AUTO_INCREMENT,
  `Nome` varchar(100) NOT NULL,
  `Email` varchar(100) NOT NULL,
  `Pass` varchar(25) NOT NULL,
  `City` varchar(25) DEFAULT NULL,
  `ImagePath` varchar(1024) DEFAULT NULL,
  `Visibility` int(11) DEFAULT '0',
  `RegisterDate` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `LastLogin` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `LastModification` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`UserID`),
  UNIQUE KEY `Email` (`Email`),
  KEY `Email_2` (`Email`,`Pass`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Users`
--

LOCK TABLES `Users` WRITE;
/*!40000 ALTER TABLE `Users` DISABLE KEYS */;
INSERT INTO `Users` VALUES (1,'Hananias','hananiasfofinho@hotmail.com','teste123',NULL,'~/images/user.png',0,'2018-11-01 10:55:27','2018-11-01 10:55:27','2018-11-01 10:55:27'),(2,'Aluno1','luizfofinho@hotmail.com','teste123','Goiana','~/images/201858011150_2.jpg',0,'2018-11-01 10:57:15','2018-11-01 10:57:15','2018-11-01 10:57:15'),(3,'Thales ','thales@hotmail.com','teste123',NULL,'~/images/user.png',0,'2018-11-01 10:59:40','2018-11-01 10:59:40','2018-11-01 10:59:40'),(4,'Aluno2','pepe@hotmail.com','teste123','Timbauba','~/images/201803011141_4.png',1,'2018-11-01 11:02:25','2018-11-01 11:02:25','2018-11-01 11:02:25'),(5,'Aluno3','jonas@hotmail.com','teste123',NULL,'~/images/user.png',0,'2018-11-01 11:04:06','2018-11-01 11:04:06','2018-11-01 11:04:06'),(6,'Alexandre','alexandre@hotmail.com','teste123','Joao pesso','~/images/201815011140_6.jpg',1,'2018-11-01 13:13:54','2018-11-01 13:13:54','2018-11-01 13:13:54'),(7,'Daniel','daniel@hotmail.com','teste123','Trindade','~/images/201822011137_7.jpg',0,'2018-11-01 13:19:52','2018-11-01 13:19:52','2018-11-01 13:19:52'),(8,'Rodrigo','rodrigo@hotmail.com','teste123','Jampa','~/images/201825011130_8.png',0,'2018-11-01 13:24:28','2018-11-01 13:24:28','2018-11-01 13:24:28'),(9,'mateus toin','mateus@hotmail.com','teste123','Goiana','~/images/201840011110_9.jpg',0,'2018-11-01 13:39:13','2018-11-01 13:39:13','2018-11-01 13:39:13'),(10,'Alan Moraes','alan@ci.com','alan123','Joao Pessoa','~/images/201819011117_10.jpg',0,'2018-11-01 14:18:41','2018-11-01 14:18:41','2018-11-01 14:18:41');
/*!40000 ALTER TABLE `Users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-11-01 18:13:53
