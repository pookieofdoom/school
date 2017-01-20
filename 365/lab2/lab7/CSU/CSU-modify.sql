-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- CSU-modify.sql


-- Keep undeclared majors from fullerton and long beach,
-- enrollments at slo w/ non-zero graduate enrollments and undergrad < 500
-- engineer enrollments > 2000 ungraduates at any csu
DELETE FROM DisciplineEnrollments
   WHERE NOT ((Campus = 7 OR Campus = 9) AND Discipline = 22
      OR (Campus = 20 AND Graduate > 0 AND Undergraduate < 500)
      OR (Discipline = 9 AND Undergraduate > 2000));
   
SELECT * FROM DisciplineEnrollments ORDER BY Campus, Discipline;

-- Keep in CSU fees (all conditions must match): fee > $2,500
-- year is either 2002 or one of 2004-2006
-- campus = SLO, Pomona or SJSU
DELETE FROM CSUFees
   WHERE NOT ((CampusFee > 2500) 
      AND (Year = 2002 OR (Year >= 2004 AND Year <= 2006))
      AND (Campus = 20 OR Campus = 14 OR Campus = 19));

SELECT * FROM CSUFees ORDER BY Campus, Year;