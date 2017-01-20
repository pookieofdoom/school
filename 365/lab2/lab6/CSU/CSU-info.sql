-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- CSU-info.sql

-- Q1
SELECT CSUFees.CampusFee
FROM Campuses, CSUFees
WHERE Campuses.Campus = 
   'California Polytechnic State University-San Luis Obispo'
   AND CSUFees.Campus = Campuses.Id AND CSUFees.Year = 2000;

-- Q2
SELECT Enrollments.Year, Enrollments.TotalEnrollment_AY
FROM Campuses, Enrollments
WHERE Campuses.Campus = 'California State University-Los Angeles'
   AND Enrollments.Year >= 1960 AND Enrollments.Year <= 1969
   AND Campuses.Id = Enrollments.Campus
ORDER BY Enrollments.Year;

-- Q3
SELECT Campuses.Campus, E.FTE_AY, F.Faculty, E.FTE_AY / F.Faculty AS SF_Ratio
FROM Campuses, Enrollments E, Faculty F
WHERE E.FTE_AY > 17000 AND E.Year = 2003 AND F.Year = 2003
   AND Campuses.Id = E.Campus AND Campuses.Id = F.Campus
ORDER BY SF_Ratio;

-- Q4
SELECT Campuses.Campus, Disciplines.Name
FROM Campuses, Disciplines, DisciplineEnrollments
WHERE Campuses.Id = DisciplineEnrollments.Campus
   AND DisciplineEnrollments.Discipline = Disciplines.Id
   AND DisciplineEnrollments.Year = 2004 
   AND DisciplineEnrollments.Undergraduate != 0
   AND DisciplineEnrollments.Graduate > (3*DisciplineEnrollments.Undergraduate)
ORDER BY Campuses.Campus, Disciplines.Name;

-- Q5
SELECT Fees.Year, Fees.CampusFee * E.FTE_AY AS Total_Student_Fees,
   Fees.CampusFee * E.FTE_AY / F.Faculty AS Fees_Per_Faculty
FROM Campuses, CSUFees Fees, Enrollments E, Faculty F
WHERE Campuses.Campus = 'Sonoma State University'
   AND Fees.Year >= 2002 AND Fees.Year <= 2004
   AND E.Year = Fees.Year AND F.Year = Fees.Year
   AND Campuses.Id = Fees.Campus AND Campuses.Id = E.Campus
   AND Campuses.Id = F.Campus
ORDER BY Fees.Year;
   
-- Q6
SELECT D_SLO.Year, D_SLO.Degrees AS 'SLO Degrees', 
   D_EB.Degrees + D_SON.Degrees AS 'EB + Son Degrees'
FROM Campuses SLO, Campuses EB, Campuses SON,
   Degrees D_SLO, Degrees D_EB, Degrees D_SON
WHERE SLO.Campus = 'California Polytechnic State University-San Luis Obispo'
   AND EB.Campus = 'California State University-East Bay'
   AND SON.Campus = 'Sonoma State University'
   AND SLO.Id = D_SLO.Campus AND EB.Id = D_EB.Campus AND SON.Id = D_SON.Campus
   AND D_SLO.Degrees > D_EB.Degrees + D_SON.Degrees
   AND D_SLO.Year = D_EB.Year AND D_SLO.Year = D_SON.Year
ORDER BY D_SLO.Year;
