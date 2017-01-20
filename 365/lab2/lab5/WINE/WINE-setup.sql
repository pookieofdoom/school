-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- WINE-setup.sql

-- DROP TABLE IF EXISTS Wine, Appellations, Grapes;


CREATE TABLE Grapes(
   Id INT,
   Grape VARCHAR(20),
   Color VARCHAR(8),
   PRIMARY KEY (Id),
   UNIQUE (Grape)
   );
   
CREATE TABLE Appellations(
   No INT,
   Appellation VARCHAR(40),
   County VARCHAR(15),
   State VARCHAR(40),
   Area VARCHAR(25),
   isAVA CHAR(3),
   PRIMARY KEY (No),
   UNIQUE (Appellation)
   );

CREATE TABLE Wine (
   No INT,
   Grape VARCHAR(20),
   Winery VARCHAR(35),
   Appellation VARCHAR(40),
   Name VARCHAR(50),
   Year INT,
   Price FLOAT,
   Score INT,
   Cases INT,
   PRIMARY KEY (No),
   FOREIGN KEY (Grape) REFERENCES Grapes(Grape),
   FOREIGN KEY (Appellation) REFERENCES Appellations(Appellation)
   );
