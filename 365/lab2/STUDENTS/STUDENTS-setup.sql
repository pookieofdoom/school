-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- STUDENTS-setup.sql

-- DROP TABLE IF EXISTS List, Teachers;


CREATE TABLE Teachers(
   LastName VARCHAR(15),
   FirstName VARCHAR(15),
   Classroom INT,
   PRIMARY KEY (Classroom),
   UNIQUE (LastName, FirstName)
   );
   
   
CREATE TABLE List(
   LastName VARCHAR(15),
   FirstName VARCHAR(15),
   Grade INT,
   Classroom INT,
   PRIMARY KEY(LastName, FirstName),
   FOREIGN KEY (Classroom) REFERENCES Teachers(Classroom)
   );
