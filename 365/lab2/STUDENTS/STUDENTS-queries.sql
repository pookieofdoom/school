-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- STUDENTS-queries.sql

-- Q1
SELECT Q.Grade, Q.ClassCounts
From (SELECT Grade, COUNT( DISTINCT Classroom) AS ClassCounts 
      FROM List 
      Group BY Grade)AS Q
WHERE Q.ClassCounts = 
   (SELECT MAX(ClassCounts) 
   FROM (SELECT Grade, COUNT( DISTINCT Classroom) AS ClassCounts 
         FROM List Group BY Grade) AS Q2)
GROUP BY Q.Grade;


-- Q2
SELECT Grade, L.LastNameCount
FROM (SELECT Grade, COUNT(LastName) as LastNameCount
      FROM List
      WHERE List.LastName LIKE "L%"
      GROUP BY Grade) AS L
WHERE L.LastNameCount = 
   (SELECT MAX(LastNameCount)
   FROM (SELECT Grade, COUNT(LastName) as LastNameCount
         FROM List
         WHERE List.LastName LIKE "L%"
         GROUP BY Grade) AS L2)
GROUP BY L.Grade;


-- Q3
SELECT S.Classroom, T.FirstName, T.LastName, S.StudentCount
FROM Teachers T, (SELECT Classroom, COUNT(LastName) AS StudentCount
                  FROM List
                  GROUP BY Classroom) AS S
WHERE S.Classroom = T.Classroom
   AND S.StudentCount = 
   (SELECT MIN(StudentCount)
   FROM (SELECT Classroom, COUNT(LastName) AS StudentCount
         FROM List
         GROUP BY Classroom) AS S2) 
GROUP BY S.Classroom;


-- Q4
SELECT COUNT(*)
FROM (SELECT Q.Classroom
      FROM (SELECT Classroom, COUNT(LastName) as avg_count
            FROM List
            GROUP BY Classroom) AS Q
      WHERE Q.avg_count < 
         (SELECT AVG(avg_count)
         FROM (SELECT Classroom, COUNT(LastName) as avg_count
               FROM List
               GROUP BY Classroom) AS Q2)
      GROUP BY Q.Classroom) AS Q3;


-- Q5
SELECT Q2.Grade, Q2.GradeCount
FROM (SELECT Classroom, COUNT(LastName) as StudentCount
      FROM List
      GROUP BY Classroom) AS Q,
      (SELECT Grade, COUNT(LastName) AS GradeCount
      From List
      GROUP BY Grade) AS Q2
WHERE Q2.GradeCount <
   (SELECT MAX(StudentCount)
   FROM (SELECT Classroom, COUNT(LastName) as StudentCount
         FROM List
         GROUP BY CLassroom) AS Q2)
GROUP BY Q2.Grade;


-- Q6
SELECT Class1.Classroom, Class2.Classroom, Class1.StudentCount 
FROM (SELECT Classroom, COUNT(LastName) as StudentCount
      FROM List
      GROUP BY Classroom)
      AS Class1,
      (SELECT Classroom, COUNT(LastName) as StudentCount
      FROM List
      GROUP BY CLassroom)
      AS Class2
WHERE Class1.Classroom > Class2.Classroom
   AND Class1.StudentCount = Class2.StudentCount
ORDER BY Class1.StudentCount;

-- Q7
SELECT G.Grade, T2.LastName
FROM (SELECT C.Grade, MAX(C.StudentCount) AS MaxStudents
      FROM (SELECT S.Grade, S.Classroom, 
               COUNT(S.LastName) AS StudentCount
            FROM List S
            GROUP BY S.Classroom) AS C
            GROUP BY C.Grade) AS T,
      (SELECT S.Grade, S.Classroom, T.LastName,
         COUNT(S.LastName) AS StudentCount
      FROM List S, Teachers T
      WHERE S.Classroom = T.Classroom
      GROUP BY S.Classroom) AS T2,
      (SELECT Grade, COUNT(DISTINCT Classroom) AS GradeCount
      FROM List
      GROUP BY Grade) AS G
WHERE T.Grade = T2.Grade AND T.MaxStudents = T2.StudentCount
   AND T.Grade = G.Grade AND G.GradeCount > 1
GROUP BY G.Grade
ORDER BY G.Grade;
