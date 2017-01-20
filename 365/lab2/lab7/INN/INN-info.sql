-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- INN-info.sql

-- Q1
SELECT roomName, decor
FROM Rooms
WHERE beds = 2 AND bedType = 'Queen' AND basePrice > 160
ORDER BY RoomId;

-- Q2
SELECT Res.LastName, Res.CheckIn, Res.CheckOut,
   Res.Adults + Res.Kids AS Total_People, Res.Rate
FROM Rooms, Reservations Res
WHERE Rooms.roomName = 'Thrift and accolade'
   AND Rooms.RoomId = Res.Room
   AND Res.CheckIn >= '2010/10/1' AND Res.CheckIn <='2010/10/31'
   AND Res.CheckOut >= '2010/10/1' AND Res.CheckOut <='2010/10/31'
   AND Rooms.basePrice > Res.Rate
ORDER BY Res.CheckIn, Res.CheckOut;

-- Q3
SELECT Rooms.roomName, Res.CheckIn, Res.CheckOut
FROM Rooms, Reservations Res
WHERE Rooms.RoomId = Res.Room
   AND Res.CheckIn <= '2010/10/24' AND Res.CheckOut >= '2010/10/24'
ORDER BY Rooms.roomName;

-- Q4
SELECT Res.Code, Res.CheckIn, Res.CheckOut, Rooms.roomName, 
   (Res.CheckOut - Res.CheckIn) * Res.Rate AS Total_Cost
FROM Rooms, Reservations Res
WHERE Res.FirstName = 'GLEN' AND Res.LastName = 'DONIGAN'
   AND Rooms.RoomId = Res.Room
ORDER BY Res.CheckIn;


-- Q5
SELECT Res.Code, Rooms.roomName, Rooms.RoomId, Res.CheckIn, Res.CheckOut
FROM Rooms, Reservations Res
WHERE Rooms.bedType = 'Double' AND Rooms.RoomId = Res.Room
   AND Res.Adults = 4
ORDER BY Res.CheckIn, Res.CheckOut, Rooms.RoomId