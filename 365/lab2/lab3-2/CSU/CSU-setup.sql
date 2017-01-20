-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- CSU-setup.sql

-- DROP TABLE IF EXISTS CSUFees, aculty, Enrollments, DisciplineEnrollments, Degrees, Disciplines, Campuses;


CREATE TABLE Campuses(
   Id INT,
   Campus VARCHAR(60),
   Location VARCHAR(20),
   County VARCHAR(20),
   Year INT,
   PRIMARY KEY (Id),
   UNIQUE (Campus)
   );
   
   
CREATE TABLE Disciplines(
   Id INT,
   Name VARCHAR(35),
   PRIMARY KEY (ID)
   );

CREATE TABLE Degrees(
   Year INT,
   Campus INT,
   Degrees INT,
   PRIMARY KEY (Year, Campus),
   FOREIGN KEY (Campus) REFERENCES Campuses(Id)
   );

CREATE TABLE DisciplineEnrollments(
   Campus INT,
   Discipline INT,
   Year INT,
   Undergraduate INT,
   Graduate INT,
   PRIMARY KEY (Campus, Discipline, Year),
   FOREIGN KEY (Campus) REFERENCES Campuses(Id),
   FOREIGN KEY (Discipline) REFERENCES Disciplines(Id)
   );

CREATE TABLE Enrollments(
   Campus INT,
   Year INT,
   TotalEnrollment_AY INT,
   FTE_AY FLOAT,
   PRIMARY KEY (Campus, Year),
   FOREIGN KEY (Campus) REFERENCES Campuses(Id)
   );
   
CREATE TABLE Faculty(
   Campus INT,
   Year INT,
   Faculty FLOAT,
   PRIMARY KEY(Campus, Year),
   FOREIGN KEY (Campus) REFERENCES Campuses(Id)
   );
   
CREATE TABLE CSUFees(
   Campus INT,
   Year INT,
   CampusFee INT,
   PRIMARY KEY(Campus, Year),
   FOREIGN KEY (Campus) REFERENCES Campuses(Id) 
   );
