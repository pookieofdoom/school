-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- INN-queries.sql

-- Q1
SELECT S.*
FROM (SELECT State, COUNT(*) AS StateCount
      FROM Marathon
      GROUP BY State) AS S
WHERE S.StateCount =
   (SELECT MAX(S2.StateCount)
   FROM (SELECT State, COUNT(*) AS StateCount
         FROM Marathon
         GROUP BY State) AS S2);

-- Q2
SELECT F.Town
FROM (SELECT Town, COUNT(*) AS FemaleCount
      FROM Marathon
      WHERE State = 'RI' AND Sex = 'F'
      GROUP BY Town) AS F,
      (SELECT Town, COUNT(*) AS MaleCount
      FROM Marathon
      WHERE State = 'RI' AND Sex = 'M'
      GROUP BY Town) AS M
WHERE F.FemaleCount > M.MaleCount AND F.Town = M.Town;

-- Q3
SELECT R.*
FROM (SELECT FirstName, LastName, Town, State, Place
      FROM Marathon
      WHERE State = 'RI' AND Town = 'WARWICK') AS R
WHERE R.Place < ANY
   (SELECT MAX(R2.Place)
   FROM (SELECT FirstName, LastName, Town, State, Place
         FROM Marathon
         WHERE State = 'MO') AS R2);

-- Q4
SELECT A.*
FROM (SELECT State, GroupRange, Sex, COUNT(*) AS NumPeople
      FROM Marathon
      GROUP BY State, GroupRange, Sex
      HAVING NumPeople > 1
      ORDER BY State, GroupRange) AS A,
      
      (SELECT B.State, MAX(B.NumPeople) AS MaxPeople
      FROM (SELECT State, GroupRange, Sex, COUNT(*) AS NumPeople
            FROM Marathon
            GROUP BY State, GroupRange, Sex
            HAVING NumPeople > 1
            ORDER BY State, GroupRange) AS B
      GROUP BY B.State) AS C
WHERE A.NumPeople = C.MaxPeople AND A.State = C.State;

-- Q5
SELECT A.*
FROM (SELECT Place, FirstName, LastName
      FROM Marathon
      WHERE Sex = 'F'
      ORDER BY Pace) AS A
LIMIT 1 OFFSET 29;




