-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- INN-count.sql

-- Q1
SELECT Rooms.RoomName, 
   SUM(Res.Rate * DATEDIFF(Res.CheckOut,Res.CheckIn)) AS TotalRev,
   AVG(Res.Rate * DATEDIFF(Res.CheckOut,Res.CheckIn)) AS AvgRev
FROM Rooms, Reservations Res
WHERE Rooms.RoomId = Res.Room 
   AND Res.CheckIn >= '2010-5-1'
   AND Res.CheckIn <= '2010-5-31'
GROUP BY Rooms.RoomName
ORDER BY TotalRev DESC;
   
-- Q2
SELECT COUNT(CheckIn) AS SaturdayCheckInCount, 
   SUM(Rate * DATEDIFF(CheckOut, CheckIn)) AS TotalRev
FROM Reservations
WHERE DAYNAME(CheckIn) = 'Saturday';
   
-- Q3
SELECT DAYNAME(CheckIn), COUNT(*),
   SUM(Rate * DATEDIFF(CheckOut, CheckIn)) AS TotalRev
FROM Reservations
GROUP BY DAYNAME(CheckIn)
ORDER BY WEEKDAY(CheckIn);

-- Q4
SELECT DATEDIFF(Res.CheckOut, Res.CheckIn) AS StayDuration, COUNT(*)
FROM Reservations Res, Rooms
WHERE Rooms.roomName = 'Frugal not apropos' AND Res.Room = Rooms.RoomId
GROUP BY StayDuration
ORDER BY StayDuration;

-- Q5
SELECT Rooms.RoomName, Rooms.RoomId, Rooms.roomName,
   SUM(DATEDIFF(
   IF(Res.CheckOut > '2010-12-31', '2010-12-31', Res.CheckOut),
   Res.CheckIn))  AS NumDays
FROM Reservations Res, Rooms
WHERE Res.Room = Rooms.RoomId 
   AND Res.CheckIn >= '2010-1-1' AND Res.CheckIn <= '2010-12-31'
GROUP BY Rooms.RoomName
ORDER BY NumDays DESC;
