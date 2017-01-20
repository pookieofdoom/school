-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- AIRLINES-modify.sql

-- Remove all flights except for those to and from AOS
DELETE FROM Flights
   WHERE NOT (SourceAirport = "AOS" OR DestAirport = "AOS");
   
-- Increase flight number by 2000 (not nw, jb, or virgin)
UPDATE Flights
   SET FlightNo = FlightNo + 2000
   WHERE NOT (Airline = 6 OR Airline = 8 OR Airline = 12);

-- temp change the odd numbers so they don't clash with uniqueness
UPDATE Flights
   SET FlightNo = FlightNo * -1
   WHERE NOT (Airline = 6 OR Airline = 8 OR Airline = 12) AND MOD(FlightNo, 2) = 1;

-- Change even Flight No. to odd Flight No.
UPDATE Flights
   SET FlightNo = FlightNo + 1
   WHERE NOT (Airline = 6 OR Airline = 8 OR Airline = 12) AND MOD(FlightNo, 2) = 0;

-- Change odd Flight No. to even Flight No. while undoing temp change
UPDATE Flights
   SET FlightNo = FlightNo * -1 - 1
   WHERE FlightNo < 0;

-- Replace Airline for all flights to NW excep t JB and Virgin
UPDATE Flights
   SET Airline = 6
   WHERE NOT (Airline = 8 OR Airline = 12);
   
SELECT * FROM Flights ORDER BY Airline, FlightNo;