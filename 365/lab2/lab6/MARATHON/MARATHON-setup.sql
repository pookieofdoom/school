-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- MARATHON-setup.sql

-- DROP TABLE IF EXISTS Marathon;


CREATE TABLE Marathon(
   Place INT,
   Time TIME,
   Pace TIME,
   GroupPlace INT,
   GroupRange VARCHAR(5),
   Age INT,
   Sex CHAR(1),
   BIBNumber INT,
   FirstName VARCHAR(15),
   LastName VARCHAR(15),
   Town VARCHAR(15),
   State CHAR(2),
   PRIMARY KEY(Place)
   );
