-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- STUDENTS-lab5.sql

-- Q1
SELECT Rest.FirstName, Rest.LastName
FROM List Mel, List Rest
WHERE Mel.FirstName = 'MEL' AND Mel.LastName = 'BALBOA'
   AND Rest.FirstName != Mel.FirstName AND Rest.LastName != Mel.LastName
   AND Rest.Classroom = Mel.Classroom AND Rest.Grade = Mel.Grade
ORDER BY Rest.LastName;

-- Q2
SELECT List.FirstName, List.LastName
FROM List, Teachers
WHERE List.Classroom = Teachers.Classroom
   AND Teachers.FirstName != 'OTHA' AND Teachers.LastName != 'MOYER'
   AND List.Grade = 1
ORDER BY List.LastName;

-- Q3
SELECT COUNT(DISTINCT Classroom) AS 'Num of Grade 2 Teachers'
FROM List
WHERE Grade = 2;

-- Q4
SELECT MIN(List.LastName) AS 'First Student in Tarring\'s room'
FROM List, Teachers
WHERE List.Classroom = Teachers.Classroom
   AND Teachers.FirstName = 'LEIA' AND Teachers.LastName = 'TARRING';