-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- BAKERY-count.sql

-- Q1
SELECT Flavor, AVG(Price), COUNT(Food)
FROM Goods
GROUP BY Flavor
HAVING COUNT(*) > 3
ORDER BY AVG(Price);

-- Q2
SELECT SUM(G.Price) AS "Total Money for Cakes in Oct"
FROM Receipts R, Items I, Goods G
WHERE R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
   AND I.Receipt = R.ReceiptNumber AND I.Item = G.Id
   AND G.Food = 'Cake';

-- Q3
SELECT R.ReceiptNumber, C.LastName, COUNT(*) AS "Number of Items",
   SUM(G.Price) AS "Total Paid"
FROM Receipts R, Items I, Goods G, Customers C
WHERE R.Date = '2007-10-17'
   AND R.ReceiptNumber = I.Receipt AND I.Item = G.Id
   AND R.CustomerId = C.Id
GROUP BY I.Receipt
ORDER BY COUNT(*) DESC;

-- Q4
SELECT DAYNAME(R.Date), R.Date, COUNT(I.Receipt), SUM(G.Price)
FROM Receipts R, Items I, Goods G
WHERE R.Date >= '2007-10-8' AND R.Date < '2007-10-15'
   AND R.ReceiptNumber = I.Receipt AND I.Item = G.Id
GROUP BY R.Date
ORDER BY R.Date;

-- Q5
SELECT R.Date
FROM Receipts R, Items I, Goods G
WHERE R.ReceiptNumber = I.Receipt AND I.Item = G.Id
   AND G.Food = 'Cake'
GROUP BY R.Date
HAVING COUNT(G.Food) > 5
ORDER BY R.Date;
