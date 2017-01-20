-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- KATZENJAMMER-queries.sql

-- Q1
SELECT B.FirstName
FROM Band B
WHERE B.FirstName NOT IN
   (SELECT B.FirstName
   FROM Band B, Instruments I
   WHERE B.Id = I.BandmateId AND I.Instrument = 'accordion');

-- Q2
SELECT S.Title
FROM Songs S
WHERE S.SongId NOT IN
   (SELECT V.SongId
   FROM Vocals V)
ORDER BY S.Title;

-- Q3
SELECT C.Title
FROM (SELECT S.SongId, S.Title, COUNT(I.Instrument) AS NumInstruments
      FROM Songs S, Instruments I
      WHERE S.SongId = I.SongId
      GROUP BY S.SongId) AS C
WHERE C.NumInstruments = 
   (SELECT MAX(C2.NumInstruments)
   FROM (SELECT S.SongId, S.Title, COUNT(I.Instrument) AS NumInstruments
         FROM Songs S, Instruments I
         WHERE S.SongId = I.SongId
         GROUP BY S.SongId) AS C2);

-- Q4
SELECT A.FirstName, A.Instrument, A.NumPlayed
FROM (SELECT B.FirstName, I.Instrument, COUNT(*) AS NumPlayed
      FROM Band B, Instruments I
      WHERE B.Id = I.BandmateId
      GROUP BY B.FirstName, I.Instrument) AS A,
      
      (SELECT A2.FirstName, MAX(A2.NumPlayed) AS FavInstrument
      FROM (SELECT B.FirstName, I.Instrument, COUNT(*) AS NumPlayed
            FROM Band B, Instruments I
            WHERE B.Id = I.BandmateId
            GROUP BY B.FirstName, I.Instrument) AS A2
      GROUP BY A2.FirstName) AS F
WHERE A.NumPlayed = F.FavInstrument AND A.FirstName = F.FirstName
ORDER BY A.FirstName;

-- Q5
SELECT A.Instrument
FROM (SELECT I.Instrument
      FROM Band B, Instruments I
      WHERE B.Id = I.BandmateId AND B.FirstName = 'Anne-Marit') AS A
WHERE A.Instrument NOT IN
   (SELECT I.Instrument
   FROM Band B, Instruments I
   WHERE B.Id = I.BandmateId AND B.FirstName != 'Anne-Marit')
ORDER BY A.Instrument;

-- Q6
SELECT P.FirstName
FROM (SELECT B.FirstName, COUNT(DISTINCT I.Instrument) AS DiffInstrument
      FROM Band B, Instruments I
      WHERE B.Id = I.BandmateId
      GROUP BY B.FirstName) AS P
WHERE P.DiffInstrument = 
   (SELECT MIN(P2.DiffInstrument)
   FROM (SELECT B.FirstName, COUNT(DISTINCT I.Instrument) AS DiffInstrument
         FROM Band B, Instruments I
         WHERE B.Id = I.BandmateId
         GROUP BY B.FirstName) AS P2);

-- Q7
SELECT A.Firstname
FROM (SELECT B.FirstName, COUNT(*) AS NumLeft
      FROM Band B, Performance P
      WHERE B.Id = P.Bandmate AND P.StagePosition = 'left'
      GROUP BY B.FirstName) AS A
WHERE A.NumLeft =
   (SELECT MAX(A2.NumLeft)
   FROM (SELECT B.FirstName, COUNT(*) AS NumLeft
         FROM Band B, Performance P
         WHERE B.Id = P.Bandmate AND P.StagePosition = 'left'
         GROUP BY B.FirstName) AS A2);

-- Q8
SELECT P.Instrument
FROM (SELECT I.Instrument, COUNT(DISTINCT I.SongId) AS NumSongs
      FROM Instruments I
      GROUP BY I.Instrument) AS P
WHERE P.NumSongs =
   (SELECT MAX(P2.NumSongs)
   FROM (SELECT I.Instrument, COUNT(DISTINCT I.SongId) AS NumSongs
         FROM Instruments I
         GROUP BY I.Instrument) AS P2);

-- Q9
SELECT TuridInstrumentCount.Instrument
FROM (SELECT A.SongId, C.Instrument, B.FirstName, 
         COUNT(*) AS NumInstruments
      FROM (SELECT S.SongId, S.Title
            FROM Songs S
            WHERE S.SongId NOT IN
               (SELECT T.SongId
               FROM Tracklists T)) AS A,
               
            (SELECT I.BandmateId, I.SongId, I.Instrument
            FROM Instruments I) AS C,
            Band B
      WHERE A.SongId = C.SongId AND B.Id = C.BandmateId
         AND B.FirstName = 'Turid'
      GROUP BY C.Instrument) AS TuridInstrumentCount
WHERE TuridInstrumentCount.NumInstruments =
   (SELECT MAX(T2.NumInstruments)
   FROM (SELECT A.SongId, C.Instrument, B.FirstName,
            COUNT(*) AS NumInstruments
         FROM (SELECT S.SongId, S.Title
               FROM Songs S
               WHERE S.SongId NOT IN
                  (SELECT T.SongId
                  FROM Tracklists T)) AS A,
                  
               (SELECT I.BandmateId, I.SongId, I.Instrument
               FROM Instruments I) AS C,
               Band B
         WHERE A.SongId = C.SongId AND B.Id = C.BandmateId
            AND B.FirstName = 'Turid'
         GROUP BY C.Instrument) AS T2);