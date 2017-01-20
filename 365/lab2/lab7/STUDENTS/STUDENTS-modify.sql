 -- Anthony Dinh
 -- adinh03@calpoly.edu
 -- CPE 365
 -- STUDENTS-modify.sql

-- Extend the database structure to include information about GPA
ALTER TABLE List
   ADD (GPA FLOAT);

-- Keep in databsaae only students from grades 3 and 4   
DELETE FROM List WHERE Grade != 3 AND Grade != 4;

-- Set GPA of fourth graders from room 110 to 3.25
UPDATE List
   SET GPA = 3.25
   WHERE Grade = 4 AND Classroom = 110;

-- Set the GPA of fourth graders from other rooms to 2.9 
UPDATE List
   SET GPA = 2.9
   WHERE Grade = 4 AND Classroom != 110;

-- Set the GPA of all third graders to 3.5
UPDATE List
   SET GPA = 3.5
   WHERE Grade = 3;


-- Set GPA of Robby Pinnell to 4.0
UPDATE List
   SET GPA = 4.0
   WHERE FirstName = "ROBBY" AND LastName = "PINNELL";

-- Set GPA of Tobie Saade to 3.7
UPDATE List
   SET GPA = 3.7
   WHERE FirstName = "TOBIE" AND LastName = "SAADE";

-- Set GPA of Cyrus Roddey to 0.3 higher than whatever it currently is
UPDATE List
   SET GPA = GPA + 0.3
   WHERE FirstName = "CYRUS" AND LastName = "RODDEY";

-- Set GPA of Crysta Groeneweg + Adrian Leaper to 25% higher than whatever it currently is
UPDATE List
   SET GPA = GPA * 1.25
   WHERE FirstName = "CRYSTA" AND LastName = "GROENEWEG" or FirstName = "ADRIAN" AND LastName = "LEAPER";

SELECT * FROM List ORDER BY GPA, Grade, LastName;
