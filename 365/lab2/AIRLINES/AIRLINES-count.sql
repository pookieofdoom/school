-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- AIRLINES-count.sql

-- Q1
SELECT F.DestAirport, A.AirportName
FROM Airports100 A, Flights F
WHERE A.AirportCode = F.DestAirport
GROUP BY F.DestAirport
HAVING COUNT(*) < 5
ORDER BY A.AirportCode;

-- Q2
SELECT COUNT(DISTINCT F2.DestAirport)
FROM Flights F1, Flights F2 
WHERE F1.SourceAirport = 'APN'
   AND F2.SourceAirport = F1.DestAirport
   AND F2.DestAirport != F1.SourceAirport;
   
-- Q3
SELECT COUNT(DISTINCT F2.DestAirport)
FROM Flights F1, Flights F2 
WHERE F1.SourceAirport = 'AID'
   AND F2.SourceAirport = F1.DestAirport
   AND F2.DestAirport != F1.SourceAirport;
   
-- Q4
SELECT A.Airline, COUNT(DISTINCT F.DestAirport)
FROM Airlines A, Flights F
WHERE F.Airline = A.id
GROUP BY A.Airline
HAVING COUNT(DISTINCT F.DestAirport) > 0
ORDER BY COUNT(DISTINCT F.DestAirport) DESC;
