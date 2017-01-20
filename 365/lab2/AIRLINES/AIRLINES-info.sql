-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- AIRLINES-info.sql

-- Q1
SELECT DISTINCT Airlines.Airline, Airlines.Abbreviation
FROM Airlines, Flights
WHERE Flights.SourceAirport = 'KKI' AND Airlines.Id = Flights.Airline
ORDER BY Airlines.Airline;

-- Q2
SELECT Flights.FlightNo, Airports100.AirportCode, Airlines.Airline
FROM Airports100, Airlines, Flights
WHERE Airlines.Id = Flights.Airline 
   AND Airports100.AirportCode = Flights.SourceAirport
   AND Flights.DestAirport = 'KKI'
   AND Airlines.Abbreviation = 'UAL'
ORDER BY Flights.FlightNo;

-- Q3
SELECT Source.FlightNo AS 'Source',
   Dest.FlightNo AS 'Dest', Airports100.AirportCode, Airports100.AirportName
FROM Airlines, Airports100, Flights Source, Flights Dest
WHERE Airlines.Id = Source.Airline AND Airlines.Id = Dest.Airline
   AND Airlines.Abbreviation = 'Northwest'
   AND Source.SourceAirport = 'AXX'
   AND Source.DestAirport = Dest.SourceAirport
   AND Dest.DestAirport != 'AXX'
   AND Dest.DestAirport = Airports100.AirportCode
ORDER BY Airports100.AirportCode;

-- Q4
SELECT F_US.SourceAirport, F_US.DestAirport
FROM Airlines US, Airlines Tran, Flights F_US, Flights F_Tran
WHERE US.Abbreviation = 'USAir' AND Tran.Abbreviation = 'AirTran'
   AND F_US.Airline = US.Id AND F_Tran.Airline = Tran.Id
   AND F_US.SourceAirport = F_Tran.SourceAirport
   AND F_US.DestAirport = F_Tran.DestAirport
   AND F_US.SourceAirport > F_US.DestAirport
ORDER BY F_US.SourceAirport;

-- Q5
SELECT DISTINCT F1.SourceAirport, Airlines.Abbreviation AS 'Airline'
FROM Airlines, Flights F1, Flights F2, Flights F3, Flights F4
WHERE Airlines.Id = F1.Airline AND Airlines.Id = F2.Airline
   AND Airlines.Id = F3.Airline AND Airlines.Id = F4.Airline
   AND F1.SourceAirport = F2.SourceAirport 
   AND F1.SourceAirport = F3.SourceAirport 
   AND F1.SourceAirport = F4.SourceAirport
   AND F1.FLightNo != F2.FlightNo
   AND F1.FlightNo != F3.FlightNo
   AND F1.FlightNo != F4.FlightNo
   AND F2.FlightNo != F3.FlightNo
   AND F2.FlightNo != F4.FlightNo
   AND F3.FlightNo != F4.FlightNo
ORDER BY F1.SourceAirport;
