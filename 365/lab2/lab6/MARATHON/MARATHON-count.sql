-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- MARATHON-count.sql

-- Q1
SELECT GroupRange, Sex, COUNT(*), MIN(Place), MAX(Place)
FROM Marathon
GROUP BY GroupRange, Sex
HAVING COUNT(*) > 10
ORDER BY GroupRange, Sex;

-- Q2
SELECT COUNT(*)
FROM Marathon M1, Marathon M2
WHERE M1.GroupRange = M2.GroupRange
   AND M1.GroupPlace = 1 AND M2.GroupPlace = 2
   AND M1.Sex = M2.Sex AND M1.State = M2.State;
   
-- Q3
SELECT MINUTE(Pace), COUNT(*)
FROM Marathon
GROUP BY MINUTE(Pace)
ORDER BY MINUTE(PACE);

-- Q4
SELECT State, COUNT(*)
FROM Marathon
WHERE GroupPlace <= 10
GROUP BY State
ORDER BY COUNT(*) DESC;

-- Q5
SELECT Town, AVG(TIME_TO_SEC(Time))
FROM Marathon
WHERE State = 'MA'
GROUP BY Town
HAVING COUNT(*) >= 6
ORDER BY AVG(TIME_TO_SEC(Time));
