-- MySQL dump 10.14  Distrib 5.5.32-MariaDB, for Linux (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.32-MariaDB

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
-- Table structure for table `log`
--

DROP TABLE IF EXISTS `log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `log` (
  `id` int(10) unsigned NOT NULL,
  `date` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `transaction` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(10) NOT NULL,
  `price` decimal(64,5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `log`
--

LOCK TABLES `log` WRITE;
/*!40000 ALTER TABLE `log` DISABLE KEYS */;
INSERT INTO `log` VALUES (6,'Fri, 11 Apr 2014 17:35:35 +0000','Buy','FB','Facebook, Inc.',100,59.19800),(6,'Fri, 11 Apr 2014 17:35:50 +0000','Buy','FB','Facebook, Inc.',100,59.17000),(6,'Fri, 11 Apr 2014 18:06:07 +0000','Buy','FB','Facebook, Inc.',10,58.97000),(6,'Fri, 11 Apr 2014 18:08:05 +0000','Buy','FB','Facebook, Inc.',10,58.89000),(6,'Fri, 11 Apr 2014 18:09:43 +0000','Buy','FB','Facebook, Inc.',10,58.88990),(6,'Fri, 11 Apr 2014 18:09:49 +0000','Buy','FB','Facebook, Inc.',10,58.88000),(6,'Fri, 11 Apr 2014 18:10:33 +0000','Buy','FB','Facebook, Inc.',10,58.75000),(6,'Fri, 11 Apr 2014 18:12:01 +0000','Buy','FB','Facebook, Inc.',10,58.77000),(6,'Fri, 11 Apr 2014 18:17:10 +0000','Sell','FB','Facebook, Inc.',700,58.80000),(6,'Fri, 11 Apr 2014 18:20:01 +0000','Sell','DWRE','DEMANDWARE, INC. ',100,52.45000),(6,'Fri, 11 Apr 2014 18:20:25 +0000','Sell','JAKK','JAKKS Pacific, In',300,8.13500),(6,'Fri, 11 Apr 2014 18:20:41 +0000','Buy','BAC','Bank of America C',50,15.90000),(8,'Fri, 11 Apr 2014 15:04:28 -0400','Buy','FB','Facebook, Inc.',10,58.00500),(8,'Fri, 11 Apr 2014 15:07:55 -0400','Buy','BAC','Bank of America C',100,15.81500),(8,'Fri, 11 Apr 2014 15:10:28 -0400','Buy','FB','Facebook, Inc.',10,58.62900),(10,'Fri, 11 Apr 2014 15:13:59 -0400','Buy','FB','Facebook, Inc.',10,58.63800),(10,'Fri, 11 Apr 2014 15:16:06 -0400','Sell','FB','Facebook, Inc.',10,58.43000),(10,'Fri, 11 Apr 2014 15:17:36 -0400','Buy','BAC','Bank of America C',100,15.85000),(10,'Fri, 11 Apr 2014 15:17:58 -0400','Sell','BAC','Bank of America C',100,15.85000);
/*!40000 ALTER TABLE `log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolio`
--

DROP TABLE IF EXISTS `portfolio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolio` (
  `id` int(10) unsigned NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolio`
--

LOCK TABLES `portfolio` WRITE;
/*!40000 ALTER TABLE `portfolio` DISABLE KEYS */;
INSERT INTO `portfolio` VALUES (6,'BAC',750),(6,'CCOI',200),(6,'PNW',100),(8,'BAC',100),(8,'FB',20);
/*!40000 ALTER TABLE `portfolio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000),(2,'hirschhorn','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000),(4,'malan','$1$HA$azTGIMVlmPi9W9Y12cYSj/',10000.0000),(5,'milo','$1$HA$6DHumQaK4GhpX8QE23C8V1',10000.0000),(6,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.',59045.5000),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000.0000),(8,'drausio','$1$aRsR2d3n$xD8eJ4e1ijzBv1VvpMimz0',10000.0000),(10,'valeria','$1$4TTbhM2I$Fh5wx7wFAMApDJptEMx2j/',9997.9200);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-04-11 15:32:19
