-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- MARATHON-info.sql

-- Q1
SELECT Place AS 'Overall Place', Time AS 'Run Time'
FROM Marathon
WHERE GroupPlace = 2 AND GroupRange = '50-59' AND Sex = 'M';

-- Q2
SELECT FirstName, LastName, Time AS 'Run Time',
   Place AS 'Overall Place', GroupPlace AS 'Gender-Age Place'
FROM Marathon
WHERE Sex = 'M' AND Town = 'CAMBRIDGE' AND State = 'MA'
ORDER BY Place;

-- Q3
SELECT female.FirstName, female.LastName, female.GroupRange AS 'Age Group',
   female.Place AS 'Overall Place', female.GroupPlace AS 'Gender-Age Place',
   female.Town AS 'Home Town'
FROM Marathon male, Marathon female
WHERE male.GroupPlace = 50 AND male.GroupRange = '40-49'
   AND female.Place < male.Place AND female.State = 'MA'
   AND male.Sex = 'M'  AND female.Sex = 'F'
ORDER BY female.Place;

-- Q4
SELECT DISTINCT M1.BIBNumber AS 'Duplicate Bib Numbers'
FROM Marathon M1, Marathon M2
WHERE M1.BIBNumber = M2.BIBNumber
   AND M1.Place != M2.Place
ORDER BY M1.BIBNumber;

-- Q5
SELECT M1.FirstName AS '1st FirstName',
   M1.LastName AS '1st LastName', M1.Age,
   M2.FirstName AS '2nd FirstName',
   M2.LastName AS '2nd LastName', M2.Age,
   M1.GroupRange, M1.Sex
FROM Marathon M1, Marathon M2
WHERE M1.GroupPlace = 1 AND M2.GroupPlace = 2
   AND M1.GroupRange = M2.GroupRange
   AND M1.Sex = M2.Sex
ORDER BY M1.Sex, M1.GroupRange
