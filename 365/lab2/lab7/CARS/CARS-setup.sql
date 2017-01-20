-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- CARS-setup.sql

-- DROP TABLE IF EXISTS CarsData, CarNames, ModelList, CarMakers, Countries, Continents;

CREATE TABLE Continents(
   ContId INT,
   Continent VARCHAR(11),
   PRIMARY KEY (ContId),
   UNIQUE (Continent)
   );
   
   
CREATE TABLE Countries(
   CountryId INT,
   CountryName VARCHAR(30),
   Continent INT,
   PRIMARY KEY (CountryId),
   FOREIGN KEY (Continent) REFERENCES Continents(ContId),
   UNIQUE(CountryName)
   );


CREATE TABLE CarMakers(
   Id INT,
   Maker VARCHAR(15),
   FullName VARCHAR(30),
   Country INT,
   PRIMARY KEY (Id),
   FOREIGN KEY (Country) REFERENCES Countries(CountryId),
   UNIQUE (FullName),
   UNIQUE (Maker)
   );
   
   
CREATE TABLE ModelList(
   ModelId INT,
   Maker INT,
   Model VARCHAR(15),
   PRIMARY KEY (ModelId),
   FOREIGN KEY (Maker) REFERENCES CarMakers(Id),
   UNIQUE (Model)
   );
   

CREATE TABLE CarNames(
   MakeId INT,
   Model VARCHAR(15),
   MakeDescription VARCHAR(40),
   PRIMARY KEY (MakeId),
   FOREIGN KEY (Model) REFERENCES ModelList(Model)
   );
   

 CREATE TABLE CarsData(
   Id INT,
   MPG FLOAT,
   Cylinders INT,
   Edispl FLOAT,
   Horsepower INT,
   Weight INT,
   Accelerate FLOAT,
   Year INT,
   PRIMARY KEY (Id),
   FOREIGN KEY (Id) REFERENCES CarNames(MakeId)
   );
