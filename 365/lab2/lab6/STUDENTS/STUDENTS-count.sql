-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- STUDENTS-count.sql

-- Q1
SELECT T.FirstName, T.LastName
FROM List S, Teachers T
WHERE T.Classroom = S.Classroom
GROUP BY T.Classroom
HAVING COUNT(*) >= 3 AND COUNT(*) <= 4
ORDER BY T.LastName;

-- Q2
SELECT Grade, COUNT(DISTINCT Classroom) AS Classes, COUNT(*) AS Students
FROM List
GROUP BY Grade
ORDER BY Classes DESC, Grade;

-- Q3
SELECT Classroom, COUNT(*) AS Students
FROM List
WHERE Grade = 4
GROUP BY Classroom
ORDER BY Students DESC; 

-- Q4
SELECT Classroom, MAX(LastName)
FROM List
WHERE Grade = 0
GROUP BY Classroom
ORDER BY Classroom;

-- Q5
SELECT DISTINCT CHAR_LENGTH(LastName) AS LastNameLen, COUNT(*) AS Students
FROM List
GROUP BY LastNameLen
ORDER BY LastNameLen;

