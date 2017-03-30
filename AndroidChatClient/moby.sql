-- phpMyAdmin SQL Dump
-- version 3.2.0.1
-- http://www.phpmyadmin.net
--
-- Anamakine: localhost
-- Üretim Zamanı: 16 Haziran 2010 saat 15:07:51
-- Sunucu sürümü: 5.1.36
-- PHP Sürümü: 5.3.0

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Veritabanı: `moby`
--

-- --------------------------------------------------------

--
-- Tablo yapısı: `dcreateinfo`
--

CREATE TABLE IF NOT EXISTS `dcreateinfo` (
  `userName` varchar(30) NOT NULL,
  `documentID` varchar(30) NOT NULL,
  `dcDate` date DEFAULT NULL,
  PRIMARY KEY (`userName`,`documentID`),
  KEY `dccons2` (`documentID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `dcreateinfo`
--

INSERT INTO `dcreateinfo` (`userName`, `documentID`, `dcDate`) VALUES
('aboz', 'd30958', '2010-06-16'),
('cozturan', 'd24243', '2010-06-15'),
('patici', 'd27788', '2010-06-12'),
('patici', 'd29461', '2010-06-12');

-- --------------------------------------------------------

--
-- Tablo yapısı: `document`
--

CREATE TABLE IF NOT EXISTS `document` (
  `documentID` varchar(30) NOT NULL,
  `documentName` varchar(100) NOT NULL,
  `documentPath` varchar(300) DEFAULT NULL,
  PRIMARY KEY (`documentID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `document`
--

INSERT INTO `document` (`documentID`, `documentName`, `documentPath`) VALUES
('d1111', 'schedule', 'projects/p3/schedule.jpg'),
('d1214', 'schedule', 'projects/p7/schedule.jpg'),
('d123', 'enYeniRapor', 'projects/p1/enYeniRapor.txt'),
('d1234', 'rapor', 'projects/p1/rapor.txt'),
('d1272', 'manual', 'projects/p2/manual.txt'),
('d2222', 'schedule', 'projects/p4/schedule.jpg'),
('d2331', 'schedule', 'projects/p2/schedule.jpg'),
('d23432', 'schedule', 'projects/p1/schedule.jpg'),
('d24243', '', 'projects/p1/'),
('d27788', 'medical.sql', 'projects/p3/medical.sql'),
('d29461', 'testNetwork.txt', 'projects/p3/testNetwork.txt'),
('d30958', 'CEM.txt', 'projects/p1/CEM.txt'),
('d325', 'schedule', 'projects/p5/schedule.jpg'),
('d342', 'schedule', 'projects/p6/schedule.jpg');

-- --------------------------------------------------------

--
-- Tablo yapısı: `dupdateinfo`
--

CREATE TABLE IF NOT EXISTS `dupdateinfo` (
  `userName` varchar(30) NOT NULL,
  `documentID` varchar(30) NOT NULL,
  `dupdateDate` date NOT NULL,
  PRIMARY KEY (`userName`,`documentID`,`dupdateDate`),
  KEY `ducons2` (`documentID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `dupdateinfo`
--


-- --------------------------------------------------------

--
-- Tablo yapısı: `ecreateinfo`
--

CREATE TABLE IF NOT EXISTS `ecreateinfo` (
  `userName` varchar(30) NOT NULL,
  `eventID` varchar(30) NOT NULL,
  `ecDate` date DEFAULT NULL,
  PRIMARY KEY (`userName`,`eventID`),
  KEY `eccons2` (`eventID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `ecreateinfo`
--

INSERT INTO `ecreateinfo` (`userName`, `eventID`, `ecDate`) VALUES
('aboz', 'e12687', '2010-06-16');

-- --------------------------------------------------------

--
-- Tablo yapısı: `eupdateinfo`
--

CREATE TABLE IF NOT EXISTS `eupdateinfo` (
  `userName` varchar(30) NOT NULL,
  `eventID` varchar(30) NOT NULL,
  `euDate` date NOT NULL DEFAULT '0000-00-00',
  PRIMARY KEY (`userName`,`eventID`,`euDate`),
  KEY `eucons2` (`eventID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `eupdateinfo`
--

INSERT INTO `eupdateinfo` (`userName`, `eventID`, `euDate`) VALUES
('aboz', 'e1', '2010-06-16'),
('aboz', 'e2', '2010-06-16'),
('patici', 'e5', '2010-06-11');

-- --------------------------------------------------------

--
-- Tablo yapısı: `event`
--

CREATE TABLE IF NOT EXISTS `event` (
  `eventName` varchar(50) NOT NULL,
  `eventID` varchar(30) NOT NULL,
  `eventDate` date NOT NULL,
  `eventAddress` varchar(100) NOT NULL,
  PRIMARY KEY (`eventID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `event`
--

INSERT INTO `event` (`eventName`, `eventID`, `eventDate`, `eventAddress`) VALUES
('Kodak representatives meeting', 'e1', '2010-07-08', 'Convention Center'),
('Sin City Meeting with Actors', 'e10', '2010-10-03', 'Ankara Rixos'),
('Sin City Director Meeting', 'e11', '2010-11-01', 'Warner Bros Studios'),
('name', 'e12687', '2010-12-12', 'bolum'),
('Kodak project evaluation of progress', 'e2', '2010-12-12', 'Convention Center'),
('Lucky Strike Introduction Meeting', 'e3', '2010-07-27', 'Meeting Center'),
('SpaceCom Work Distribution', 'e5', '2010-06-09', 'Convention Center'),
('Warfare Simulator Meeting', 'e6', '2010-08-24', 'Meeting Center'),
('Nike Com. First Meeting', 'e7', '2010-04-06', 'Hilton,Istanbul'),
('Nike Product Presentation', 'e8', '2010-04-21', 'Ankara Crown Plaza'),
('Nike Commercial Role Sharing', 'e9', '2010-05-01', 'Convention Center');

-- --------------------------------------------------------

--
-- Tablo yapısı: `hasdocument`
--

CREATE TABLE IF NOT EXISTS `hasdocument` (
  `projectID` varchar(30) NOT NULL,
  `documentID` varchar(30) NOT NULL,
  PRIMARY KEY (`projectID`,`documentID`),
  KEY `hdcons2` (`documentID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `hasdocument`
--

INSERT INTO `hasdocument` (`projectID`, `documentID`) VALUES
('p3', 'd1111'),
('p7', 'd1214'),
('p1', 'd123'),
('p1', 'd1234'),
('p2', 'd1272'),
('p4', 'd2222'),
('p2', 'd2331'),
('p1', 'd23432'),
('p1', 'd24243'),
('p3', 'd27788'),
('p3', 'd29461'),
('p1', 'd30958'),
('p5', 'd325'),
('p6', 'd342');

-- --------------------------------------------------------

--
-- Tablo yapısı: `hasevent`
--

CREATE TABLE IF NOT EXISTS `hasevent` (
  `projectID` varchar(30) NOT NULL,
  `eventID` varchar(30) NOT NULL,
  PRIMARY KEY (`projectID`,`eventID`),
  KEY `hcons2` (`eventID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `hasevent`
--

INSERT INTO `hasevent` (`projectID`, `eventID`) VALUES
('p1', 'e1'),
('p6', 'e10'),
('p6', 'e11'),
('p1', 'e12687'),
('p2', 'e12687'),
('p3', 'e12687'),
('p4', 'e12687'),
('p5', 'e12687'),
('p6', 'e12687'),
('p7', 'e12687'),
('p1', 'e2'),
('p5', 'e3'),
('p2', 'e5'),
('p3', 'e6'),
('p7', 'e7'),
('p7', 'e8'),
('p7', 'e9');

-- --------------------------------------------------------

--
-- Tablo yapısı: `hasnotification`
--

CREATE TABLE IF NOT EXISTS `hasnotification` (
  `userName` varchar(30) NOT NULL,
  `notificationID` varchar(30) NOT NULL,
  `time` date DEFAULT NULL,
  PRIMARY KEY (`userName`,`notificationID`),
  KEY `hncons2` (`notificationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `hasnotification`
--


-- --------------------------------------------------------

--
-- Tablo yapısı: `haspersonalmessage`
--

CREATE TABLE IF NOT EXISTS `haspersonalmessage` (
  `userName` varchar(30) NOT NULL,
  `messageID` varchar(30) NOT NULL,
  PRIMARY KEY (`userName`,`messageID`),
  KEY `hpcons2` (`messageID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `haspersonalmessage`
--

INSERT INTO `haspersonalmessage` (`userName`, `messageID`) VALUES
('cozturan', 'm10294'),
('aboz', 'm124'),
('jdepp', 'm13071'),
('aboz', 'm20141'),
('cozturan', 'm22121'),
('cozturan', 'm23580'),
('aboz', 'm26082'),
('swilliams', 'm3184'),
('cozturan', 'm32668'),
('mozkul', 'm3493'),
('nportman', 'm4206'),
('jdepp', 'm5585'),
('rgonzalez', 'm7145'),
('patici', 'm8665');

-- --------------------------------------------------------

--
-- Tablo yapısı: `messagecreate`
--

CREATE TABLE IF NOT EXISTS `messagecreate` (
  `userName` varchar(30) NOT NULL,
  `messageID` varchar(30) NOT NULL,
  `mcDate` date DEFAULT NULL,
  `mcTime` time DEFAULT NULL,
  PRIMARY KEY (`userName`,`messageID`),
  KEY `mccons2` (`messageID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `messagecreate`
--

INSERT INTO `messagecreate` (`userName`, `messageID`, `mcDate`, `mcTime`) VALUES
('aboz', 'm124', '2010-05-18', '01:30:00'),
('aboz', 'm20141', '2010-06-15', '16:21:49'),
('aboz', 'm26082', '2010-06-15', '16:22:47'),
('cozturan', 'm10294', '2010-06-13', '12:23:01'),
('cozturan', 'm22121', '2010-06-16', '10:21:05'),
('cozturan', 'm23580', '2010-06-16', '11:07:35'),
('cozturan', 'm32668', '2010-06-15', '14:33:31'),
('jdepp', 'm13071', '2010-06-15', '14:29:45'),
('jdepp', 'm5585', '2010-06-13', '12:22:00'),
('mozkul', 'm3493', '2010-06-15', '14:34:02'),
('nportman', 'm4206', '2010-06-15', '14:28:44'),
('patici', 'm8665', '2010-05-25', '15:37:12'),
('rgonzalez', 'm7145', '2010-06-15', '14:25:57'),
('swilliams', 'm3184', '2010-06-15', '14:25:28');

-- --------------------------------------------------------

--
-- Tablo yapısı: `notification`
--

CREATE TABLE IF NOT EXISTS `notification` (
  `notificationID` varchar(30) NOT NULL,
  `notificationType` varchar(20) NOT NULL,
  `text` varchar(300) NOT NULL,
  PRIMARY KEY (`notificationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `notification`
--


-- --------------------------------------------------------

--
-- Tablo yapısı: `participants`
--

CREATE TABLE IF NOT EXISTS `participants` (
  `eventID` varchar(30) NOT NULL,
  `userName` varchar(30) NOT NULL,
  PRIMARY KEY (`eventID`,`userName`),
  KEY `pcons2` (`userName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `participants`
--


-- --------------------------------------------------------

--
-- Tablo yapısı: `pcreateinfo`
--

CREATE TABLE IF NOT EXISTS `pcreateinfo` (
  `userName` varchar(30) NOT NULL,
  `projectID` varchar(30) NOT NULL,
  PRIMARY KEY (`userName`,`projectID`),
  KEY `pccons2` (`projectID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `pcreateinfo`
--


-- --------------------------------------------------------

--
-- Tablo yapısı: `personalmessage`
--

CREATE TABLE IF NOT EXISTS `personalmessage` (
  `messageID` varchar(30) NOT NULL,
  `messageType` varchar(20) NOT NULL,
  `message` varchar(300) DEFAULT NULL,
  `sender` varchar(30) NOT NULL,
  PRIMARY KEY (`messageID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `personalmessage`
--

INSERT INTO `personalmessage` (`messageID`, `messageType`, `message`, `sender`) VALUES
('m10294', 'text', 'I admire you Cem...', 'Natalie Portman'),
('m124', 'text', 'Ahmet bey sizinle acil gorusmemiz gerek.', 'Gizem Albayrak'),
('m13071', 'text', 'I will be meeting you on 15th of June, Tuesday at 1 p.m.', 'Pelin Atici'),
('m20141', 'text', 'Ahmet bey yeni basladiginiz is hayatinizda basarilar dilerim.', 'Rusen Aktas'),
('m22121', 'text', 'New message', 'Ahmet Boz'),
('m23580', 'text', 'yeni mesaj', 'Mehmet Boz'),
('m26082', 'text', 'Ahmet Bey, sizinle yeni projedeki görev da&#287;&#305;l&#305;mlar&#305; hakk&#305;nda konu&#351;mam&#305;z gerek. Biraz adaletsiz durumlar var ve bu ko&#351;ullarda projeyi yeti&#351;tirmemiz zor görünüyor.', 'Cem Ozturan'),
('m3184', 'text', 'I expect you to come on 2nd May Tuesday.', 'Ali Cengiz'),
('m32668', 'text', 'Simülasyon projenize yeni özellikler eklemeniz için görü&#351;memiz gerek.', 'Ahmet Boz'),
('m3493', 'text', 'Ödül töreni için ön görü&#351;me yar&#305;n 15.00te olacak.', 'Ahmet Boz'),
('m4206', 'text', 'Your new movie selection is on Tuesday.', 'Ali Cengiz'),
('m5585', 'text', 'I love you Johnny!', 'Natalie Portman'),
('m7145', 'text', 'I expect you to come on 5th of May Wednesday.', 'Ali Cengiz'),
('m8665', 'text', 'pelin hanima sevgiler.', 'Ahmet Boz');

-- --------------------------------------------------------

--
-- Tablo yapısı: `project`
--

CREATE TABLE IF NOT EXISTS `project` (
  `projectName` varchar(50) NOT NULL,
  `projectID` varchar(30) NOT NULL,
  `startDate` date NOT NULL,
  `deadline` date DEFAULT NULL,
  `projectDescrpt` varchar(1000) DEFAULT NULL,
  PRIMARY KEY (`projectID`),
  KEY `projectIndex` (`projectID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `project`
--

INSERT INTO `project` (`projectName`, `projectID`, `startDate`, `deadline`, `projectDescrpt`) VALUES
('Kodak S310 TV Commercial', 'p1', '2008-02-02', '2011-02-02', 'Kodak first launched the Kodak Smart Picture Frame on the QVC shopping channel in the fourth quarter of 2000, at a time when the majority of consumers didn''t know about or understand this new category. Kodak''s Smart Frame was designed by Weave Innovations and licensed to Kodak with an exclusive relationship with Weave''s StoryBox online photo network.[14] Smart Frame owners connected to the network via an analog telephone connection built into the frame. The frame was configured to default connect at 2 a.m. to download new pictures off the Story Box network. The other option to load images onto the frame was via the CompactFlash port. The retail price was $349 USD. The frame could hold 36 images internally and came with a six-month free subscription to the StoryBox network.'),
('SpaceCom', 'p2', '2010-05-20', '2010-11-15', 'SPACE.com, launched in 1999, is the world''s No. 1 source for news of astronomy, skywatching, space exploration, commercial spaceflight and related technologies.  Our team of experienced reporters, editors and video producers explore the latest discoveries, missions, trends and futuristic ideas, interviewing expert sources and offering up deep and broad analysis of the findings and issues that are fundamental to or understanding of the universe and our place in it.  SPACE.com articles are regularly featured on the web sites of our media partners: AOL, FoxNews.com, MSNBC.com and Yahoo. '),
('Warfare Simulator', 'p3', '2010-05-26', '2010-11-17', 'Harpoon is more than a computer naval game … it’s a true naval warfare simulation. The Harpoon products allow you to simulate air/sub/surface and power projection, at a tactical-operational scale, using hundreds of pre-built scenarios or your own custom resources.  Updated several times a year the products cover a range of fidelity and ease of use.  Harpoon has it covered! Look for the Harpoon Utlimate bundle in March 2010.  Featuring v3.10 of Harpoon 3 ANW and and updated Harpoon Commander''s Edition.     Harpoon is the premier modern naval warfare simulation. It grew out of the Harpoon board game designed by Larry Bond in the 1980s, the one used by author Tom Clancy in writing The Hunt for Red October and Red Storm Rising.'),
('Ship Bridge Simulator', 'p4', '2010-05-18', '2010-10-05', 'Virtual Reality within Virtual Reality courtesy of the view from Bridge 1 at the Lairdside Maritime Centre, the UK''s most advanced 360-degree Ships Bridge Simulator suite.  Incorporating two similarly equipped secondary bridges for simultaneous interactive single and multiple ship training scenarios, three instructor control stations, a Global Maritime Distress & Safety System (GMDSS) control station and a Vessel Traffic Services (VTS) control station, the Centre provides an exceptionally realistic, versatile and, most importantly, completely safe virtual reality environment for training, research and role-play.  Kongsberg''s legendary Norcontrol Polaris Ships Bridge Simulator hardware (incorporating radar, ECDIS, GPS, Loran-C and AIS navigational aids, a GMDSS communications system, and bridge elements that can be repositioned or replaced in order to facilitate specific ship type training or a particular client''s needs), and SeaView R5 software (incorporating an oceanographics statisti'),
('Lucky Strike Commercial', 'p5', '2010-05-26', '2010-08-02', 'Lucky Strike is a famous brand of American cigarettes, often referred to as "Luckies".. The brand was first introduced by R.A. Patterson of Richmond, Virginia, in 1871 as cut-plug chewing tobacco and later a cigarette. In 1905, the company was acquired by the American Tobacco Company (ATC), and Lucky Strike would later prove to be its answer to R.J. Reynolds'' Camel.  In 1917, the brand started using the slogan "It''s Toasted" to inform consumers about the manufacturing method in which the tobacco is toasted rather than sun-dried, a process touted as making the cigarette''s taste more desirable. The message "L.S.M.F.T." ("Lucky Strike means fine tobacco") was introduced on the package in the same year.  Lucky Strike''s association with radio music programs began during the 1920s on NBC. By 1928, the bandleader and vaudeville producer B. A. Rolfe was performing on radio and recording as "B.A. Rolfe and his Lucky Strike Orchestra" for Edison Records. In 1935, ATC began to sponsor Your Hit Pa'),
('Sin City Movie Production', 'p6', '2010-09-22', '2011-06-03', 'in City (full title: Frank Miller''s Sin City)[2] is a 2005 American crime thriller film written, produced, and directed by Frank Miller and Robert Rodriguez. It is a film noir based on Miller''s graphic novel series of the same name.  The film is primarily based on three of Miller''s works: The Hard Goodbye, about a man who embarks on a brutal rampage in search of his one-time sweetheart''s killer; The Big Fat Kill, which focuses on a street war between a group of prostitutes and a group of mercenaries; and That Yellow Bastard, which follows an aging police officer who protects a young woman from a grotesquely disfigured serial killer. The movie stars Bruce Willis, Alexis Bledel, Mickey Rourke, Jessica Alba, Clive Owen, Michael Clarke Duncan, Rosario Dawson, Benicio del Toro, Michael Madsen, Nick Stahl, Powers Boothe, Josh Hartnett, Jaime King, Brittany Murphy, Elijah Wood and Rutger Hauer, among others.  Sin City opened to wide critical and commercial success, gathering particular recogn'),
('Nike Write The Future Commercial', 'p7', '2010-04-07', '2010-06-09', 'Nike, Inc. (pronounced /ˈnaɪkiː/) (NYSE: NKE) is a major publicly traded sportswear and equipment supplier based in the United States. The company is headquartered near Beaverton, Oregon, which is part of the Portland metropolitan area. It is the world''s leading supplier of athletic shoes and apparel[4] and a major manufacturer of sports equipment with revenue in excess of $18.6 billion USD in its fiscal year 2008 (ending May 31, 2008). As of 2008, it employed more than 30,000 people worldwide. Nike and Precision Castparts are the only Fortune 500 companies headquartered in the state of Oregon, according to The Oregonian.  The company was founded on January 25, 1964 as Blue Ribbon Sports by Bill Bowerman and Philip Knight, and officially became Nike, Inc. in 1978. The company takes its name from Nike (Greek Νίκη pronounced [níːkɛː]), the Greek goddess of victory. Nike markets its products under its own brand as well as Nike Golf, Nike Pro, Nike+, Air Jordan, Nike Skateboarding and subs');

-- --------------------------------------------------------

--
-- Tablo yapısı: `user`
--

CREATE TABLE IF NOT EXISTS `user` (
  `userName` varchar(30) NOT NULL,
  `name` varchar(30) NOT NULL,
  `surname` varchar(30) NOT NULL,
  `password` varchar(30) NOT NULL,
  PRIMARY KEY (`userName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `user`
--

INSERT INTO `user` (`userName`, `name`, `surname`, `password`) VALUES
('aboz', 'Mehmet', 'Boz', 'ahmet'),
('acengiz', 'Ali', 'Cengiz', 'ali'),
('cozturan', 'Cem', 'Ozturan', 'cem'),
('galbayrak', 'Gizem', 'Albayrak', 'gizem'),
('jdepp', 'Johnny', 'Depp', 'johnny'),
('mozkul', 'Munir', 'Ozkul', 'munir'),
('nportman', 'Natalie', 'Portman', 'natalie'),
('patici', 'Pelin', 'Atici', 'palenko'),
('raktas', 'Rusen', 'Aktas', 'rusen'),
('rgonzalez', 'Raul', 'Gonzalez', 'raul'),
('swilliams', 'Serena', 'Williams', 'serena');

-- --------------------------------------------------------

--
-- Tablo yapısı: `worksin`
--

CREATE TABLE IF NOT EXISTS `worksin` (
  `userName` varchar(30) NOT NULL,
  `projectID` varchar(30) NOT NULL,
  `since` date DEFAULT NULL,
  PRIMARY KEY (`userName`,`projectID`),
  KEY `userName` (`userName`,`projectID`),
  KEY `cons2` (`projectID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Tablo döküm verisi `worksin`
--

INSERT INTO `worksin` (`userName`, `projectID`, `since`) VALUES
('aboz', 'p1', '2009-02-02'),
('aboz', 'p5', '2010-05-30'),
('acengiz', 'p1', '2010-06-01'),
('cozturan', 'p2', '2010-03-02'),
('cozturan', 'p3', '2010-03-02'),
('cozturan', 'p4', '2010-04-06'),
('galbayrak', 'p2', '2010-01-06'),
('galbayrak', 'p3', '2010-06-02'),
('galbayrak', 'p4', '2010-06-01'),
('jdepp', 'p6', '2010-10-12'),
('mozkul', 'p6', '2010-10-03'),
('nportman', 'p6', '2010-10-15'),
('patici', 'p2', '2010-05-24'),
('patici', 'p3', '2010-06-01'),
('patici', 'p4', '2010-06-01'),
('raktas', 'p1', '2010-06-09'),
('raktas', 'p5', '2010-01-06'),
('raktas', 'p7', '2010-05-04'),
('rgonzalez', 'p7', '2010-04-14'),
('swilliams', 'p7', '2010-04-20');

--
-- Dökümü yapılmış tablolar için kısıtlamalar
--

--
-- Tablo kısıtlamaları `dcreateinfo`
--
ALTER TABLE `dcreateinfo`
  ADD CONSTRAINT `dccons1` FOREIGN KEY (`userName`) REFERENCES `user` (`userName`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `dccons2` FOREIGN KEY (`documentID`) REFERENCES `document` (`documentID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Tablo kısıtlamaları `dupdateinfo`
--
ALTER TABLE `dupdateinfo`
  ADD CONSTRAINT `ducons1` FOREIGN KEY (`userName`) REFERENCES `user` (`userName`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `ducons2` FOREIGN KEY (`documentID`) REFERENCES `document` (`documentID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Tablo kısıtlamaları `ecreateinfo`
--
ALTER TABLE `ecreateinfo`
  ADD CONSTRAINT `eccons1` FOREIGN KEY (`userName`) REFERENCES `user` (`userName`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `eccons2` FOREIGN KEY (`eventID`) REFERENCES `event` (`eventID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Tablo kısıtlamaları `eupdateinfo`
--
ALTER TABLE `eupdateinfo`
  ADD CONSTRAINT `eucons1` FOREIGN KEY (`userName`) REFERENCES `user` (`userName`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `eucons2` FOREIGN KEY (`eventID`) REFERENCES `event` (`eventID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Tablo kısıtlamaları `hasdocument`
--
ALTER TABLE `hasdocument`
  ADD CONSTRAINT `hdcons1` FOREIGN KEY (`projectID`) REFERENCES `project` (`projectID`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `hdcons2` FOREIGN KEY (`documentID`) REFERENCES `document` (`documentID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Tablo kısıtlamaları `hasevent`
--
ALTER TABLE `hasevent`
  ADD CONSTRAINT `hcons1` FOREIGN KEY (`projectID`) REFERENCES `project` (`projectID`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `hcons2` FOREIGN KEY (`eventID`) REFERENCES `event` (`eventID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Tablo kısıtlamaları `hasnotification`
--
ALTER TABLE `hasnotification`
  ADD CONSTRAINT `hncons1` FOREIGN KEY (`userName`) REFERENCES `user` (`userName`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `hncons2` FOREIGN KEY (`notificationID`) REFERENCES `notification` (`notificationID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Tablo kısıtlamaları `haspersonalmessage`
--
ALTER TABLE `haspersonalmessage`
  ADD CONSTRAINT `hpcons1` FOREIGN KEY (`userName`) REFERENCES `user` (`userName`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `hpcons2` FOREIGN KEY (`messageID`) REFERENCES `personalmessage` (`messageID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Tablo kısıtlamaları `messagecreate`
--
ALTER TABLE `messagecreate`
  ADD CONSTRAINT `mccons1` FOREIGN KEY (`userName`) REFERENCES `user` (`userName`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `mccons2` FOREIGN KEY (`messageID`) REFERENCES `personalmessage` (`messageID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Tablo kısıtlamaları `participants`
--
ALTER TABLE `participants`
  ADD CONSTRAINT `pcons1` FOREIGN KEY (`eventID`) REFERENCES `event` (`eventID`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `pcons2` FOREIGN KEY (`userName`) REFERENCES `user` (`userName`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Tablo kısıtlamaları `pcreateinfo`
--
ALTER TABLE `pcreateinfo`
  ADD CONSTRAINT `pccons1` FOREIGN KEY (`userName`) REFERENCES `user` (`userName`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `pccons2` FOREIGN KEY (`projectID`) REFERENCES `project` (`projectID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Tablo kısıtlamaları `worksin`
--
ALTER TABLE `worksin`
  ADD CONSTRAINT `cons1` FOREIGN KEY (`userName`) REFERENCES `user` (`userName`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `cons2` FOREIGN KEY (`projectID`) REFERENCES `project` (`projectID`) ON DELETE CASCADE ON UPDATE CASCADE;
