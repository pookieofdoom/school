-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- KATZENJAMMER-lab5.sql

-- Q1
SELECT COUNT(*)
FROM Instruments I, Band B
WHERE B.FirstName = 'Turid' AND B.Id = I.BandmateId
   AND (I.Instrument = 'bass balalaika' OR I.Instrument = 'bass');

-- Q2
SELECT COUNT(*)
FROM Band Anne, Band Solveig, Performance P, Instruments I
WHERE Anne.FirstName = 'Anne-Marit' AND Solveig.FirstName = 'Solveig'
   AND P.StagePosition = 'center' AND I.Instrument = 'drums'
   AND Anne.Id = P.Bandmate AND Solveig.Id = I.BandmateId
   AND P.SongId = I.SongId;

-- Q3
SELECT COUNT(*)
FROM Band Solveig, Band Turid, Vocals V, Performance P
WHERE Solveig.Id = V.Bandmate AND Turid.Id = P.Bandmate
   AND Solveig.FirstName = 'Solveig' AND Turid.FirstName = 'Turid'
   AND V.Type = 'lead' AND P.StagePosition != 'back'
   AND V.SongId = P.SongId;

-- Q4
SELECT COUNT(DISTINCT I.Instrument)
FROM Band B, Instruments I
WHERE B.FirstName = 'Anne-Marit' AND B.Id = I.BandmateId;

-- Q5
SELECT DISTINCT I1.Instrument
FROM Band Anne, Band Solveig, Instruments I1, Instruments I2
WHERE Anne.FirstName = 'Anne-Marit' AND Solveig.FirstName = 'Solveig'
   AND I1.BandmateId = Anne.Id AND I2.BandmateId = Solveig.Id
   AND I1.Instrument = I2.Instrument;

-- Q6
SELECT COUNT(DISTINCT I.BandmateId)
FROM Instruments I
WHERE I.Instrument = 'accordion';

-- Q7
SELECT COUNT(*)
FROM Instruments I1, Instruments I2
WHERE I1.SongId = I2.SongId
   AND I1.BandmateId > I2.BandmateId
   AND I1.Instrument = I2.Instrument;

-- Q8
SELECT COUNT(*)
FROM Band B1, Band B2, Band B3, Band B4, 
   Performance P1, Performance P2, Performance P3, Performance P4
WHERE B1.FirstName = 'Marianne' AND B1.Id = P1.Bandmate 
   AND P1.StagePosition = 'right'
   AND B2.FirstName = 'Turid' AND B2.Id = P2.Bandmate
   AND P2.StagePosition = 'center'
   AND B3.FirstName = 'Solveig' AND B3.Id = P3.Bandmate
   AND P3.StagePosition = 'back'
   AND B4.FirstName = 'Anne-Marit' AND B4.Id = P4.Bandmate
   AND P4.StagePosition = 'left'
   AND P1.SongId = P2.SongId AND P1.SongId = P3.SongId 
   AND P1.SongId = P4.SongId AND P2.SongId = P3.SongId 
   AND P2.SongId = P4.SongId AND P3.SongId = P4.SongId;

-- Q9
SELECT DISTINCT B1.FirstName AS 'Right', B2.FirstName AS 'Center',
   B3.FirstName AS 'Back', B4.FirstName AS 'Left'
FROM Band B1, Band B2, Band B3, Band B4, 
   Performance P1, Performance P2, Performance P3, Performance P4
WHERE B1.Id = P1.Bandmate AND B2.Id = P2.Bandmate 
   AND B3.Id = P3.Bandmate AND B4.Id = P4.Bandmate
   AND P1.StagePosition = 'right' AND P2.StagePosition = 'center'
   AND P3.StagePosition = 'back' AND P4.StagePosition = 'left'
   AND P1.SongId = P2.SongId AND P1.SongId = P3.SongId 
   AND P1.SongId = P4.SongId AND P2.SongId = P3.SongId 
   AND P2.SongId = P4.SongId AND P3.SongId = P4.SongId
ORDER BY B1.FirstName, B2.FirstName, B3.FirstName, B4.FirstName;

-- Q10
SELECT DISTINCT P1.StagePosition AS 'Turid', P2.StagePosition AS 'Solveig',
   P3.StagePosition AS 'Marianne', P4.StagePosition AS 'Anne-Marit'
FROM Band B1, Band B2, Band B3, Band B4, 
   Performance P1, Performance P2, Performance P3, Performance P4
WHERE B1.Id = P1.Bandmate AND B2.Id = P2.Bandmate 
   AND B3.Id = P3.Bandmate AND B4.Id = P4.Bandmate
   AND B1.FirstName = 'Turid' AND B2.FirstName = 'Solveig'
   AND B3.FirstName = 'Marianne' AND B4.FirstName = 'Anne-Marit'
   AND P1.StagePosition != P2.StagePosition 
   AND P1.StagePosition != P3.StagePosition
   AND P1.StagePosition != P4.StagePosition
   AND P2.StagePosition != P3.StagePosition
   AND P2.StagePosition != P4.StagePosition
   AND P3.StagePosition != P4.StagePosition
   AND P1.SongId = P2.SongId AND P1.SongId = P3.SongId 
   AND P1.SongId = P4.SongId AND P2.SongId = P3.SongId 
   AND P2.SongId = P4.SongId AND P3.SongId = P4.SongId
ORDER BY P1.StagePosition, P2.StagePosition, P3.StagePosition, P4.StagePosition;

