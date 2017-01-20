-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- AIRLINES-setup.sql

-- DROP TABLE IF EXISTS Flights, Airlines, Airports100;


CREATE TABLE Airports100(
   City VARCHAR(25),
   AirportCode VARCHAR(3),
   AirportName VARCHAR(50),
   Country VARCHAR(25),
   CountryAbbrev VARCHAR(3),
   PRIMARY KEY (AirportCode)
   );
   
   
CREATE TABLE Airlines(
   id INT,
   Airline VARCHAR(20),
   Abbreviation VARCHAR(20),
   Country VARCHAR(25),
   PRIMARY KEY (id),
   UNIQUE (Airline),
   UNIQUE (Abbreviation)
   );
   

CREATE TABLE Flights(
   Airline INT,
   FlightNo INT,
   SourceAirport VARCHAR(3),
   DestAirport VARCHAR(3),
   PRIMARY KEY (Airline, FlightNo),
   FOREIGN KEY (Airline) REFERENCES Airlines(id),
   FOREIGN KEY (SourceAirport) REFERENCES Airports100(AirportCode),
   FOREIGN KEY (DestAirport) REFERENCES Airports100(AirportCode)
   );
