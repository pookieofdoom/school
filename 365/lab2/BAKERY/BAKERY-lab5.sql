-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- BAKERY-lab5.sql

-- Q1
SELECT DISTINCT C.FirstName, C.LastName
FROM Customers C, Receipts R1, Receipts R2
WHERE C.Id = R1.CustomerId AND C.Id = R2.CustomerId
   AND R1.Date = R2.Date AND R1.ReceiptNumber > R2.ReceiptNumber
   AND R1.Date >= '2007-10-5' AND R1.DATE <= '2007-10-11'
ORDER BY C.LastName;

-- Q2
SELECT DISTINCT C.FirstName, C.LastName
FROM Goods G1, Goods G2, Customers C, Items I1, Items I2, Receipts R
WHERE C.Id = R.CustomerId 
   AND R.ReceiptNumber = I1.Receipt AND R.ReceiptNumber = I2.Receipt
   AND I1.Item = G1.Id AND I2.Item = G2.Id
   AND I1.Ordinal != I2.Ordinal 
   AND G1.Food = G2.Food AND G1.Flavor = G2.Flavor
   AND G1.Food = 'Cookie'
ORDER BY C.LastName;

-- Q3
SELECT DISTINCT G.Food, G.Flavor, G.Price
FROM Customers C, Goods G, 
   Receipts R1, Receipts R2, Receipts R3, Items I1, Items I2, Items I3
WHERE C.FirstName = 'STEPHEN' AND C.LastName = 'ZEME'
   AND C.Id = R1.CustomerId AND C.Id = R2.CustomerId AND C.Id = R3.CustomerId
   AND R1.ReceiptNumber = I1.Receipt 
   AND R2.ReceiptNumber = I2.Receipt 
   AND R3.ReceiptNumber = I3.Receipt
   AND R1.ReceiptNumber != R2.ReceiptNumber 
   AND R1.ReceiptNumber != R3.ReceiptNumber 
   AND R2.ReceiptNumber != R3.ReceiptNumber
   AND I1.Item = I2.Item AND I1.Item = I3.Item AND I2.Item = I3.Item
   AND I1.Item = G.Id
ORDER BY G.Price;


-- Q4
SELECT DISTINCT R.Date
FROM Customers C, Receipts R
WHERE C.FirstName = 'RUPERT' AND C.LastName = 'HELING'
   AND R.CustomerId = C.Id

UNION

SELECT DISTINCT R.Date
FROM Customers C, Receipts R, Goods G, Items I
WHERE C.Id = R.CustomerId
   AND R.ReceiptNumber = I.Receipt
   AND I.Item= G.Id
   AND G.Flavor = 'Gongolais' AND G.Food = 'Cookie'
ORDER BY Date;

-- Q5
SELECT SUM(G.Price) AS 'Total Money of Rayford Spoko'
FROM Customers C, Receipts R, Goods G, Items I
WHERE C.Id = R.CustomerId
   AND R.ReceiptNumber = I.Receipt
   AND I.Item = G.Id
   AND C.FirstName = 'RAYFORD' AND C.LastName = 'SOPKO'
   AND R.Date >= '2007-10-1' AND R.DATE <= '2007-10-31';
   
-- Q6
SELECT SUM(G.Price) AS 'Total Money spent on Lemon + Cherry Tarts'
FROM Receipts R, Goods G, Items I
WHERE R.ReceiptNumber = I.Receipt
   AND I.Item = G.Id
   AND (G.Flavor = 'Lemon' OR G.Flavor = 'Cherry')
   AND G.Food = 'Tart'
   AND R.Date >= '2007-10-1' AND R.Date <= '2007-10-31';
   
-- Q7
SELECT COUNT(*) 
FROM Items I
WHERE I.Ordinal = 5;

