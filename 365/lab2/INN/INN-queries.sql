-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- INN-queries.sql

-- Q1
SELECT R.roomName, R.Room, R.NumRes
FROM (SELECT Res.Room, Rooms.roomName, COUNT(*) AS NumRes
      FROM Reservations Res, Rooms
      WHERE Res.Room = Rooms.RoomId
      GROUP BY Res.Room) AS R
WHERE R.NumRes = 
   (SELECT MAX(R2.NumRes)
   FROM (SELECT Res.Room, Rooms.roomName, COUNT(*) AS NumRes
         FROM Reservations Res, Rooms
         WHERE Res.Room = Rooms.RoomId
         GROUP BY Res.Room) AS R2);

-- Q2
SELECT R.roomName, R.Room, R.Days
FROM (SELECT Rooms.roomName, Res.Room, 
         SUM(DATEDIFF(Res.CheckOut, Res.CheckIn)) AS Days
      FROM Reservations Res, Rooms
      WHERE Res.Room = Rooms.RoomId
      GROUP BY Res.Room) AS R
WHERE R.Days =
   (SELECT MIN(R2.Days)
   FROM(SELECT Rooms.roomName, Res.Room, 
         SUM(DATEDIFF(Res.CheckOut, Res.CheckIn)) AS Days
      FROM Reservations Res, Rooms
      WHERE Res.Room = Rooms.RoomId
      GROUP BY Res.Room) AS R2);

-- Q3
SELECT P.*
FROM (SELECT Rooms.roomName, Res.CheckIn, Res.CheckOut,
         Res.LastName, Res.Rate,
         Res.Rate * DATEDIFF(Res.CheckOut, Res.CheckIn) AS TotalPaid
      FROM Reservations Res, Rooms
      WHERE Res.Room = Rooms.RoomId) AS P
WHERE P.TotalPaid = 
   (SELECT MAX(Res.Rate * DATEDIFF(Res.CheckOut, Res.CheckIn))
   FROM Reservations Res, Rooms
   WHERE Res.Room = Rooms.RoomId);

-- Q4
SELECT P.*
FROM (SELECT Rooms.roomName, Res.CheckIn, Res.CheckOut,
         Res.LastName, Res.Rate,
         Res.Rate * DATEDIFF(Res.CheckOut, Res.CheckIn) AS TotalPaid
      FROM Reservations Res, Rooms
      WHERE Res.Room = Rooms.RoomId) AS P,
      
      (SELECT P2.roomName, MAX(P2.TotalPaid) AS MaxTotalPaid
      FROM (SELECT Rooms.roomName,
               Res.Rate * DATEDIFF(Res.CheckOut, Res.CheckIn) AS TotalPaid
            FROM Reservations Res, Rooms
            WHERE Res.Room = Rooms.RoomId) AS P2
      GROUP BY P2.roomName) AS MaxPaidRoom
WHERE P.TotalPaid = MaxPaidRoom.MaxTotalPaid AND P.roomName = MaxPaidRoom.roomName
ORDER BY P.TotalPaid DESC;

-- Q5
SELECT P.*
FROM (SELECT MONTHNAME(Res.CheckIn) AS Month, COUNT(*) AS NumRes,
         SUM(Res.Rate * DATEDIFF(Res.CheckOut, Res.CheckIn)) AS TotalPaid
      FROM Reservations Res
      GROUP BY MONTHNAME(Res.CheckIn)) AS P,
      
      (SELECT MAX(M.TotalPaid) AS MaxPay
      FROM (SELECT MONTHNAME(Res.CheckIn) AS Month, COUNT(*) AS NumRes,
               SUM(Res.Rate * DATEDIFF(Res.CheckOut, Res.CheckIn)) AS TotalPaid
            FROM Reservations Res
            GROUP BY MONTHNAME(Res.CheckIn)) AS M) AS M2
WHERE P.TotalPaid = M2.MaxPay;

-- Q6
SELECT Rooms.roomName, Rooms.RoomId, 'Empty' AS OccupiedStatus
FROM Rooms
WHERE Rooms.roomName NOT IN
   (SELECT Rooms.roomName
      FROM Reservations Res, Rooms 
      WHERE Res.CheckIn <= '2010-5-5' AND Res.CheckOut > '2010-5-5'
         AND Rooms.RoomId = Res.Room)
UNION

SELECT Rooms.roomName, Rooms.RoomId, 'Occupied' AS OccupiedStatus
FROM Reservations Res, Rooms 
WHERE Res.CheckIn <= '2010-5-5' AND Res.CheckOut > '2010-5-5'
   AND Rooms.RoomId = Res.Room
   
ORDER BY RoomId;

-- Q7
SELECT Rooms.roomName, COUNT(Res.Room)
FROM (SELECT Res.Room, MAX(Res.Rate) AS MaxRate
      FROM Reservations Res
      GROUP BY Res.Room) AS MaxTable,
      Reservations Res, Rooms
WHERE Res.Room = Rooms.RoomId AND Res.Room = MaxTable.Room
   AND Res.Rate = MaxTable.MaxRate
GROUP BY Rooms.roomName
ORDER BY COUNT(Res.Room);

