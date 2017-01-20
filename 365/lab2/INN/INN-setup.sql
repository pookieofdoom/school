-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- INN-setup.sql

-- DROP TABLE IF EXISTS Reservations, Rooms;


CREATE TABLE Rooms(
   RoomId CHAR(5),
   roomName VARCHAR(25),
   beds INT,
   bedType VARCHAR(20),
   maxOccupancy INT,
   basePrice INT,
   decor VARCHAR(20),
   PRIMARY KEY (RoomId),
   UNIQUE (roomName)
   );
   

CREATE TABLE Reservations(
   Code INT,
   Room CHAR(3),
   CheckIn DATE,
   CheckOut DATE,
   Rate FLOAT,
   LastName VARCHAR(15),
   FirstName VARCHAR(15),
   Adults INT CHECK (Adults >=1),
   Kids INT,
   PRIMARY KEY (Code),
   FOREIGN KEY (Room) REFERENCES Rooms(RoomId),
   UNIQUE (Room, CheckIn)
   );
