-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- KATZENJAMMER-modify.sql 

-- update the length of Instrument
ALTER TABLE Instruments
   MODIFY Instrument VARCHAR(25);

-- replace occurances of bass balaika and guitar
UPDATE Instruments
   SET Instrument = 'awesome bass balalaika'
   WHERE Instrument = 'bass balalaika';

UPDATE Instruments
   SET Instrument = 'acoustic guitar'
   WHERE Instrument = 'guitar';

-- Keep only information about acoustic guitar and Turid
DELETE FROM Instruments
   WHERE NOT (Instrument = 'acoustic guitar' OR  BandmateId = 4);

SELECT * FROM Instruments ORDER BY SongId, BandmateId;

-- add attribute to keep track of total number of songs in album
ALTER TABLE Albums
   ADD(Total INT);

UPDATE Albums
   SET Total = 13
   WHERE AId = 1;

UPDATE Albums
   SET Total = 12
   WHERE AId = 2;

UPDATE Albums
   SET Total = 19
   WHERE AId = 3;

UPDATE Albums
   SET Total = 11
   WHERE AId = 4;

SELECT * FROM Albums ORDER BY Year;
