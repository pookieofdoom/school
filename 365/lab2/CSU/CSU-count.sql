-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- CSU-count.sql

-- Q1
SELECT C.Campus, SUM(D.Degrees)
FROM Campuses C, Enrollments E, Degrees D
WHERE E.Year >= 1990 AND E.Year <= 1999
   AND E.Campus = C.Id AND D.Campus = C.ID
   AND D.Year = E.Year
GROUP BY C.Campus
HAVING AVG(TotalEnrollment_AY) > 20000
ORDER BY C.Campus;

-- Q2
SELECT C.Campus, AVG(E.TotalEnrollment_AY) AS 'Avg Enrollments', 
   MAX(E.TotalEnrollment_AY) AS 'Max Enrollments',
   MIN(E.TotalEnrollment_AY) AS 'Min Enrollments'
FROM Campuses C, Enrollments E
WHERE C.Id = E.Campus
GROUP BY C.Campus
HAVING MAX(E.Year) - MIN(E.Year) > 60
ORDER BY AVG(E.TotalEnrollment_AY);

-- Q3
SELECT D.Year, SUM(D.Degrees), SUM(F.Faculty)
FROM Degrees D, Faculty F
WHERE D.Year >= 2002 AND D.Year <= 2004
   AND F.Year = D.Year AND D.Campus = F.Campus
GROUP BY D.Year
ORDER BY D.Year;

-- Q4
SELECT C.Campus, COUNT(D.Discipline)
FROM Campuses C, Enrollments E, DisciplineEnrollments D
WHERE C.Id = E.Campus AND C.Id = D.Campus 
   AND E.Year = 2004 AND D.Year = E.Year
   AND E.TotalEnrollment_AY > 20000
   AND D.Graduate > 0
GROUP BY C.Campus
ORDER BY C.Campus