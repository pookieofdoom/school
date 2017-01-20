-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- WINE-modify.sql

-- Remove columns storing Appellation name and name of the wine
ALTER TABLE Wine
   DROP FOREIGN KEY Wine_ibfk_2,
   DROP Appellation,
   DROP Name;

-- Keep in wine table only the Zinfandels with score of 93 or higher
DELETE FROM Wine WHERE NOT(Grape = "Zinfandel" AND Score >= 93);

-- Modify the length of the attribue storing the winery name to be 18 char long
ALTER TABLE Wine
   MODIFY Winery VARCHAR(18);

SELECT * FROM Wine ORDER BY No;

-- Create new column called Revenue in the wines table
ALTER TABLE Wine
   ADD (Revenue FLOAT);

-- Compute the expected revenue (case contains 12 wines)
UPDATE Wine
   SET Revenue = Cases * 12 * Price;

-- Keep only the wines with the expected revenue exeeding $150,000
DELETE FROM Wine WHERE Revenue < 150000;
   
   
SELECT * FROM Wine ORDER BY No;
