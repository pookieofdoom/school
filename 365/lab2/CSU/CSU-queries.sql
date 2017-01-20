-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- CSU-queries.sql

-- Q1
SELECT C.Campus, SUM(DE.Undergraduate)
FROM Campuses C, Enrollments E, DisciplineEnrollments DE
WHERE C.Id = E.Campus AND C.Id = DE.Campus
   AND E.TotalEnrollment_AY = 
      (SELECT MAX(E.TotalEnrollment_AY)
      FROM Enrollments E
      WHERE E.Year = 1965);
      
-- Q2
SELECT C.Campus, S.SumDeg
FROM (SELECT D.Campus, SUM(D.Degrees) AS SumDeg
            FROM Degrees D
            GROUP BY D.Campus) AS S,
      Campuses C
WHERE C.Id = S.Campus 
   AND S.SumDeg =
      (SELECT MAX(S2.SumDeg)
      FROM (SELECT D.Campus, SUM(D.Degrees) AS SumDeg
            FROM Degrees D
            GROUP BY D.Campus) AS S2);

-- Q3
SELECT AllCampusRatio.Campus, AllCampusRatio.SF_Ratio
FROM (SELECT C.Campus, E.FTE_AY / F.Faculty AS SF_Ratio
      FROM Campuses C, Enrollments E, Faculty F
      WHERE C.Id = E.Campus AND C.Id = F.Campus 
         AND E.Year = 2003 AND F.Year = 2003
      GROUP BY C.Campus) AS AllCampusRatio
WHERE AllCampusRatio.SF_Ratio =
   (SELECT MIN(AllCampusRatio2.SF_Ratio) 
   FROM (SELECT C.Campus, E.FTE_AY / F.Faculty AS SF_Ratio
         FROM Campuses C, Enrollments E, Faculty F
         WHERE C.Id = E.Campus AND C.Id = F.Campus 
            AND E.Year = 2003 AND F.Year = 2003
         GROUP BY C.Campus) AS AllCampusRatio2);

-- Q4
SELECT P.Campus, P.PercentSocial
FROM (SELECT C.Campus, DE.Undergraduate, E.TotalEnrollment_AY, 
         100 * DE.Undergraduate / E.TotalEnrollment_AY AS PercentSocial
      FROM Campuses C, DisciplineEnrollments DE, Enrollments E, Disciplines D
      WHERE C.Id = DE.Campus AND C.Id = E.Campus
         AND D.Name = 'Social Sciences' AND D.Id = DE.Discipline
         AND DE.Year = 2004 AND E.Year = 2004) AS P
WHERE P.PercentSocial =
   (SELECT MAX(P2.PercentSocial)
   FROM (SELECT C.Campus, DE.Undergraduate, E.TotalEnrollment_AY, 
            100 * DE.Undergraduate / E.TotalEnrollment_AY AS PercentSocial
         FROM Campuses C, DisciplineEnrollments DE,
            Enrollments E, Disciplines D
         WHERE C.Id = DE.Campus AND C.Id = E.Campus
            AND D.Name = 'Social Sciences' AND D.Id = DE.Discipline
            AND DE.Year = 2004 AND E.Year = 2004) AS P2);

-- Q5
SELECT R.CurrentYear, R.Campus
FROM (SELECT C.Campus, E1.Year AS LastYear, E2.Year AS CurrentYear,
         (E2.TotalEnrollment_AY - E1.TotalEnrollment_AY) 
         /(E2.TotalEnrollment_AY) * 100 AS RelativeIncrease
      FROM Campuses C, Enrollments E1, Enrollments E2
      WHERE C.Id = E1.Campus AND C.Id = E2.Campus
         AND E2.Year >= 1998 AND E2.Year <= 2003 AND C.Year < 1998
         AND E1.Year = E2.Year - 1) AS R,
         
      (SELECT R2.CurrentYear, MAX(R2.RelativeIncrease) AS BestIncrease
      FROM (SELECT C.Campus, E1.Year AS LastYear, E2.Year AS CurrentYear,
            (E2.TotalEnrollment_AY - E1.TotalEnrollment_AY) 
            /(E2.TotalEnrollment_AY) * 100 AS RelativeIncrease
            FROM Campuses C, Enrollments E1, Enrollments E2
            WHERE C.Id = E1.Campus AND C.Id = E2.Campus
               AND E2.Year >= 1998 AND E2.Year <= 2003 AND C.Year < 1998
               AND E1.Year = E2.Year - 1) AS R2
      GROUP BY R2.CurrentYear) AS R3     
WHERE R.CurrentYear = R3.CurrentYear AND R.RelativeIncrease = R3.BestIncrease
ORDER BY R.CurrentYear;
            
-- Q6
SELECT R.Year, R.Campus, R.Ratio
FROM (SELECT C.Campus, D.Year,
         D.Degrees / E.TotalEnrollment_AY AS Ratio
      FROM Campuses C, Enrollments E, Degrees D
      WHERE C.Id = E.Campus AND C.Id = D.Campus
         AND E.Year >= 1997 AND E.Year <= 2003 
         AND D.Year = E.Year) AS R,
      (SELECT M.Year, MAX(M.Ratio) AS MaxRatio
      FROM (SELECT C.Campus, D.Year,
               D.Degrees / E.TotalEnrollment_AY AS Ratio
            FROM Campuses C, Enrollments E, Degrees D
            WHERE C.Id = E.Campus AND C.Id = D.Campus
               AND E.Year >= 1997 AND E.Year <= 2003 
               AND D.Year = E.Year) AS M
      GROUP BY M.Year) AS MaxRatioPerYear
WHERE R.Ratio = MaxRatioPerYear.MaxRatio
ORDER BY R.Year;

-- Q7     
SELECT A1.Campus, A1.Year, A1.SF_Ratio
FROM (SELECT C.Campus, E.Year,  E.FTE_AY / F.Faculty AS SF_Ratio
      FROM Campuses C, Enrollments E, Faculty F
      WHERE C.Id = E.Campus AND C.Id = F.Campus AND E.Year = F.Year
      GROUP BY C.Campus, E.Year) AS A1,
      (SELECT A2.Campus, MIN(A2.SF_Ratio) AS MinRatio
      FROM (SELECT C.Campus, E.Year,  E.FTE_AY / F.Faculty AS SF_Ratio
            FROM Campuses C, Enrollments E, Faculty F
            WHERE C.Id = E.Campus AND C.Id = F.Campus AND E.Year = F.Year
            GROUP BY C.Campus, E.Year) AS A2
      GROUP BY A2.Campus) AS B
WHERE A1.SF_Ratio = MinRatio
ORDER BY A1.Campus;

-- Q8
SELECT TheList.Campus
FROM (SELECT A1.Campus, A1.Year, A1.SF_Ratio
      FROM (SELECT C.Campus, E.Year,  E.FTE_AY / F.Faculty AS SF_Ratio
            FROM Campuses C, Enrollments E, Faculty F
            WHERE C.Id = E.Campus AND C.Id = F.Campus AND E.Year = F.Year
            GROUP BY C.Campus, E.Year) AS A1,
            (SELECT A2.Campus, MIN(A2.SF_Ratio) AS MinRatio
            FROM (SELECT C.Campus, E.Year,  E.FTE_AY / F.Faculty AS SF_Ratio
                  FROM Campuses C, Enrollments E, Faculty F
                  WHERE C.Id = E.Campus AND C.Id = F.Campus AND E.Year = F.Year
                  GROUP BY C.Campus, E.Year) AS A2
            GROUP BY A2.Campus) AS B
      WHERE A1.SF_Ratio = MinRatio) AS TheList
WHERE TheList.SF_Ratio =
   (SELECT MAX(TheList2.SF_Ratio)
   FROM (SELECT A1.Campus, A1.Year, A1.SF_Ratio
         FROM (SELECT C.Campus, E.Year,  E.FTE_AY / F.Faculty AS SF_Ratio
               FROM Campuses C, Enrollments E, Faculty F
               WHERE C.Id = E.Campus AND C.Id = F.Campus AND E.Year = F.Year
               GROUP BY C.Campus, E.Year) AS A1,
               (SELECT A2.Campus, MIN(A2.SF_Ratio) AS MinRatio
               FROM (SELECT C.Campus, E.Year,  E.FTE_AY / F.Faculty AS SF_Ratio
                     FROM Campuses C, Enrollments E, Faculty F
                     WHERE C.Id = E.Campus AND C.Id = F.Campus 
                        AND E.Year = F.Year
                     GROUP BY C.Campus, E.Year) AS A2
               GROUP BY A2.Campus) AS B
         WHERE A1.SF_Ratio = MinRatio) AS TheList2);
            
            
