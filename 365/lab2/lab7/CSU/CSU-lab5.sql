-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- CSU-lab5.sql

-- Q1
SELECT SUM(D.Degrees) AS 'Total Degegrees from SLO (1995 - 2000)'
FROM Campuses C, Degrees D
WHERE C.Id = D.Campus
   AND C.Campus = 'California Polytechnic State University-San Luis Obispo'
   AND D.Year >= 1995 AND D.Year <= 2000;

-- Q2
SELECT MAX(F.CampusFee) AS 'Largest Fee', MIN(F.CampusFee) AS 'Lowest Fee',
   AVG(F.CampusFee) AS 'Average Fee'
FROM CSUFees F
WHERE F.Year = 2005;

-- Q3
SELECT AVG(E.FTE_AY / F.Faculty) AS 'Average students to faculty'
FROM Enrollments E, Faculty F
WHERE E.Campus = F.Campus
   AND E.Year = 2004 AND E.FTE_AY > 15000
   AND F.Year = E.Year;

-- Q4
SELECT E.Year
FROM Enrollments E, Campuses C
WHERE E.Campus = C.Id 
   AND C.Campus = 'California Polytechnic State University-San Luis Obispo' 
   AND E.TotalEnrollment_AY > 17000

UNION

SELECT D.Year
FROM Campuses C, Degrees D
WHERE C.Id = D.Campus
   AND C.Campus = 'California Polytechnic State University-San Luis Obispo' 
   AND D.Degrees > 3500
ORDER BY Year;

-- Q5
SELECT SUM(F.CampusFee * D_E.Graduate) AS 'Total Fees for Graduate Students in 2004 (All CSU)'
FROM CSUFees F, DisciplineEnrollments D_E
WHERE F.Campus = D_E.Campus
   AND F.Year = 2004 AND F.Year = D_E.Year;

-- Q6
SELECT AVG(E1.TotalEnrollment_AY) - AVG(E2.TotalEnrollment_AY), AVG(E1.FTE_AY) - AVG(E2.FTE_AY), AVG(D1.Degrees) - AVG(D2.Degrees)
FROM Enrollments E1, Degrees D1, Campuses C1,
   Enrollments E2, Degrees D2, Campuses C2
WHERE E1.Campus = C1.Id AND D1.Campus = C1.Id
   AND C1.Campus = 'California Polytechnic State University-San Luis Obispo'
   AND E2.Campus = C2.Id AND D2.Campus = C2.Id
   AND C2.Campus = 'California State Polytechnic University-Pomona';

