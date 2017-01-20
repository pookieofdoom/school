-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- KATZENJAMMER-info.sql

-- Q1
SELECT Songs.Title AS 'Rockland Album'
FROM Albums, Songs, Tracklists
WHERE Albums.Title = 'Rockland' AND Albums.AId = Tracklists.AlbumId
   AND Songs.SongId = Tracklists.SongId
ORDER BY Tracklists.Position;

-- Q2
SELECT Band.Firstname, I.Instrument
FROM Songs, Instruments I, Band
WHERE Songs.Title = 'Shine Like Neon Rays' AND Songs.SongId = I.SongId
   AND I.BandmateId = Band.Id
ORDER BY Band.Firstname;

-- Q3
SELECT DISTINCT I.Instrument AS 'Turid Instruments'
FROM Instruments I, Band
WHERE I.BandmateId = Band.Id AND Band.Firstname = 'Turid'
ORDER BY I.Instrument;

-- Q4
SELECT Songs.Title AS 'Solveig ukalele songs'
FROM Instruments I, Band, Songs
WHERE I.Instrument = 'ukalele' AND I.BandmateId = Band.Id
   AND I.SongId = Songs.SongId AND Band.Firstname = 'Solveig'
ORDER BY Songs.Title;

-- Q5
SELECT DISTINCT I.Instrument AS 'Marianne Instruments when Lead Vocal'
FROM Instruments I, Band, Vocals
WHERE Vocals.SongId = I.SongId AND Vocals.Bandmate = Band.Id
   AND Vocals.Type = 'lead' AND Band.Firstname = 'Marianne'
   AND I.BandmateId = Band.Id 
ORDER BY I.Instrument;

-- Q6
SELECT DISTINCT Songs.Title
FROM Songs, Instruments I1, Instruments I2, Instruments I3, Band
WHERE Band.Firstname = 'Anne-Marit' AND Band.Id = I1.BandmateId
   AND Band.Id = I2.BandmateId AND Band.Id = I3.BandmateId
   AND Songs.SongId = I1.SongId AND Songs.SongId = I2.SongId
   AND Songs.SongId = I3.SongId AND I1.Instrument != I2.Instrument
   AND I1.Instrument != I3.Instrument AND I2.Instrument != I3.Instrument;
   
-- Q7
SELECT M1.Firstname AS 'Right', M2.Firstname AS 'Center',
   M3.Firstname AS 'Back', M4.Firstname AS 'Left'
FROM Songs, Band M1, Band M2, Band M3, Band M4, 
   Performance R, Performance C, Performance B, Performance L
WHERE Songs.Title= 'A Bar In Amsterdam'
   AND Songs.SongId = R.SongId AND Songs.SongId = C.SongId
   AND Songs.SongId = B.SongId AND Songs.SongId = L.SongId
   AND R.StagePosition = 'right' AND C.StagePosition = 'center'
   AND B.StagePosition = 'back' AND L.StagePosition = 'left'
   AND M1.Id = R.Bandmate AND M2.Id = C.Bandmate
   AND M3.Id = B.Bandmate AND M4.Id = L.Bandmate;
   
-- Q8
SELECT Songs.Title, L.Firstname
FROM Songs, Band T, Band A, Band L, Instruments I, Vocals, Performance P
WHERE T.Firstname = 'Turid' AND I.Instrument = 'bass balalaika' 
   AND I.BandmateId = T.Id AND A.Firstname = 'Anne-Marit'
   AND P.StagePosition = 'left' AND Songs.SongId = I.SongId
   AND Songs.SongId = P.SongId AND Songs.SongId = Vocals.SongId
   AND Vocals.Type = 'lead' AND L.Id = Vocals.Bandmate AND P.Bandmate = A.Id
ORDER BY Songs.Title;
