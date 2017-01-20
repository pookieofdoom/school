-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- KATZENJAMMER-count.sql

-- Q1
SELECT B.Firstname, COUNT(*)
FROM Band B, Vocals V
WHERE V.Bandmate = B.Id AND V.Type = 'lead'
GROUP BY B.Firstname
ORDER BY COUNT(*) DESC;

-- Q2
SELECT B.Firstname, COUNT(DISTINCT I.Instrument)
FROM Instruments I, Songs S, Band B, Albums A, Tracklists T
WHERE B.Id = I.BandmateId AND I.SongId = S.SongId
   AND A.Title = 'Rockland' AND A.AId = T.AlbumId
   AND T.SongId = S.SongId
GROUP BY B.Firstname
ORDER BY B.Firstname;

-- Q3
SELECT P.StagePosition, COUNT(*) 
FROM Band B, Performance P
WHERE B.Firstname = 'Solveig'
   AND P.Bandmate = B.Id
GROUP BY P.StagePosition
ORDER BY COUNT(*);

-- Q4
Select B2.Firstname, COUNT(*)
FROM Band B1, Band B2, Performance P, Instruments I
WHERE B1.Id = P.Bandmate
   AND B1.Firstname = 'Anne-Marit' AND P.StagePosition = 'left'
   AND B2.Firstname != B1.Firstname AND (I.Instrument = 'bass balalaika'
   OR I.Instrument = 'bass') AND P.SongId = I.SongId AND I.BandmateId = B2.Id
GROUP BY B2.Firstname;

-- Q5
SELECT Instrument
FROM Instruments
GROUP BY Instrument
HAVING COUNT(DISTINCT BandmateId) = 4
ORDER BY Instrument;

-- Q6
SELECT B.Firstname, COUNT(DISTINCT I1.SongId)
FROM Band B, Instruments I1, Instruments I2
WHERE B.Id = I1.BandmateId AND I2.BandmateId = I1.BandmateId
   AND I1.Instrument != I2.Instrument
   AND I2.SongId = I1.SongId
GROUP BY B.Firstname
ORDER BY B.Firstname;

-- Q7
SELECT B.Firstname, COUNT(DISTINCT I.Instrument)
FROM Band B, Instruments I
WHERE B.Id = I.BandmateId
GROUP BY B.Firstname
ORDER BY B.Firstname;