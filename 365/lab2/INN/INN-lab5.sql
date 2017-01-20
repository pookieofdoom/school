-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- INN-lab5.sql

-- Q1
SELECT DISTINCT R1.roomName, R1.RoomId
FROM Rooms R1,
   Reservations Res1, Reservations Res2, Reservations Res3
WHERE R1.RoomId = Res1.Room 
   AND Res1.Room = Res2.Room AND Res1.Room = Res3.Room 
   AND Res2.Room = Res3.Room
   AND Res1.Code != Res2.Code AND Res1.Code != Res3.Code
   AND Res2.Code != Res3.Code
   AND Res1.CheckIn <= '2010-6-1' AND Res1.CheckOut >= '2010-6-1'
   AND Res2.CheckIn <= '2010-8-5' AND Res2.Checkout >= '2010-8-5'
   AND Res3.CheckIn <= '2010-12-1' AND Res3.Checkout >= '2010-12-1'
ORDER BY R1.roomName;

-- Q2
SELECT DISTINCT R2.FirstName, R2.LastName
FROM Reservations R1, Reservations R2
WHERE R1.FirstName = 'JONE' AND R1.LastName = 'GOON'
   AND R2.CheckIn <= R1.CheckOut  AND R2.CheckOut >= R1.CheckIn
   AND R2.FirstName != 'Jone' AND R2.LastName !='GOON'
ORDER BY R2.LastName;

-- Q3
SELECT COUNT(R.CheckIn)
FROM Reservations R, Rooms 
WHERE R.CheckIn >= '2010-8-1' AND R.Checkout <= '2010-9-30'
   AND R.Adults = 1 AND R.Kids = 0
   AND Rooms.RoomId = R.Room
   AND Rooms.beds = 2;

-- Q4
SELECT MAX(Res.CheckOut - Res.CheckIn), AVG(Res.CheckOut - Res.CheckIn)
FROM Reservations Res, Rooms
WHERE Rooms.RoomId = Res.Room
   AND Rooms.decor = 'modern'
   AND Res.CheckIn >= '2010-5-1' AND Res.CheckOut < '2010-8-31';

-- Q5
SELECT SUM(Rate * (Res.CheckOut - Res.CheckIn))
FROM Reservations Res, Rooms
WHERE Rooms.RoomId = Res.Room
   AND Rooms.roomName = 'Recluse and defiance';
   
-- Q6
SELECT SUM(Rate * (Res.CheckOut - Res.CheckIn))
FROM Reservations Res, Rooms
WHERE Rooms.RoomId = Res.Room
   AND Rooms.roomName = 'Recluse and defiance'
   AND Res.Rate < Rooms.basePrice;
