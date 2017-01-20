-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- KATZENJAMMER-setup.sql

-- DROP TABLE IF EXISTS Vocals, Performance, Instruments, Tracklists, Albums, Songs, Band;


CREATE TABLE Band(
   Id INT,
   Firstname VARCHAR(10),
   Lastname VARCHAR(10),
   PRIMARY KEY (Id),
   UNIQUE (Lastname)
   );

CREATE TABLE Songs(
   SongId INT,
   Title VARCHAR(35),
   PRIMARY KEY (SongId),
   UNIQUE (Title)
   );
   
CREATE TABLE Albums(
   AId INT,
   Title VARCHAR(40),
   Year INT,
   Label VARCHAR(22),
   Type VARCHAR(6),
   PRIMARY KEY (AId),
   UNIQUE (Title)
   );
   
CREATE TABLE Tracklists(
   AlbumId INT,
   Position INT,
   SongId INT,
   PRIMARY KEY (AlbumId, Position),
   FOREIGN KEY (AlbumId) REFERENCES Albums(AId),
   FOREIGN KEY (SongId) REFERENCES Songs(SongId)
   ); 

CREATE TABLE Instruments(
   SongId INT,
   BandmateId INT,
   Instrument VARCHAR(15),
   PRIMARY  KEY (SongId, BandmateId, Instrument),
   FOREIGN KEY (SongId) REFERENCES Songs(SongId),
   FOREIGN KEY (BandmateId) REFERENCES Band(Id)
   );

CREATE TABLE Performance(
   SongId INT,
   Bandmate INT,
   StagePosition VARCHAR(7),
   PRIMARY KEY (SongId, Bandmate),
   FOREIGN KEY (SongId) REFERENCES Songs(SongId),
   FOREIGN KEY (Bandmate) REFERENCES Band(Id)
   );
   
CREATE TABLE Vocals(
   SongId INT,
   Bandmate INT,
   Type VARCHAR(7),
   PRIMARY KEY (SongId, Bandmate, Type),
   FOREIGN KEY (SongId) REFERENCES Songs(SongId),
   FOREIGN KEY (Bandmate) REFERENCES Band(Id)
   );
