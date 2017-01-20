-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- STUDENTS-info.sql

-- Q1
SELECT List.FirstName, List.LastName
FROM List
WHERE Classroom = 102
ORDER BY LastName;

-- Q2
SELECT DISTINCT List.Classroom, List.Grade
FROM List
ORDER BY Grade, Classroom;

-- Q3
SELECT List.FirstName, List.LastName
FROM Teachers, List
WHERE Teachers.Classroom = List.Classroom 
   AND Teachers.LastName = 'KRIENER' AND Teachers.FirstName = 'BILLIE'
ORDER BY List.LastName;

-- Q4
SELECT R.FirstName, R.LastName, S.FirstName, S.LastName
FROM List R, List S
WHERE R.FirstName = S.FirstName AND R.Classroom > S.Classroom;

-- Q5
SELECT DISTINCT Teachers.FirstName, Teachers.LastName, List.Grade
FROM Teachers, List
WHERE Teachers.Classroom = List.Classroom AND List.Grade > 2 AND List.Grade < 7
ORDER BY List.Grade, Teachers.LastName
