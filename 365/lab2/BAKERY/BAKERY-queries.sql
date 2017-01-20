-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- BAKERY-queries.sql

-- Q1
SELECT C.FirstName, C.LastName
FROM (SELECT C.FirstName, C.LastName, SUM(G.Price) AS TotalPrice
      FROM Customers C, Receipts R, Goods G, Items I
      WHERE R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
         AND R.CustomerId = C.Id AND I.Receipt = R.ReceiptNumber
         AND I.Item = G.Id
      GROUP BY C.FirstName) AS C
WHERE C.TotalPrice = 
   (SELECT MAX(TotalPrice)
   FROM (SELECT SUM(G.Price) AS TotalPrice
         FROM Customers C, Receipts R, Goods G, Items I
         WHERE R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
            AND R.CustomerId = C.Id AND I.Receipt = R.ReceiptNumber
            AND I.Item = G.Id
         GROUP BY C.FirstName) AS C2);


-- Q2
SELECT C.FirstName, C.LastName
FROM Customers C
WHERE C.Id NOT IN 
   (SELECT DISTINCT C.Id
   FROM Customers C, Receipts R, Goods G, Items I
   WHERE R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
      AND R.CustomerId = C.Id AND I.Receipt = R.ReceiptNumber
      AND I.Item = G.Id AND G.Food = 'Twist')
ORDER BY C.LastName;

-- Q3
SELECT F.Food, F.Flavor
FROM (SELECT G.Food, G.Flavor, SUM(G.Price) AS SumPrice
      FROM Goods G, Items I
      WHERE G.Id = I.Item
      GROUP BY G.Id) AS F
WHERE F.SumPrice =
   (SELECT MAX(SumPrice)
   FROM (SELECT G.Food, G.Flavor, SUM(G.Price) AS SumPrice
         FROM Goods G, Items I
         WHERE G.Id = I.Item
         GROUP BY G.Id) AS F2);

-- Q4
SELECT F.Food, F.Flavor
FROM (SELECT G.Food, G.Flavor, COUNT(G.Food) AS TotalSold
      FROM Goods G, Items I
      WHERE G.Id = I.Item
      GROUP BY G.Id) AS F
WHERE F.TotalSold = 
   (SELECT MAX(TotalSold)
   FROM (SELECT G.Food, G.Flavor, COUNT(G.Food) AS TotalSold
         FROM Goods G, Items I
         WHERE G.Id = I.Item
         GROUP BY G.Id) AS F2);

-- Q5
SELECT D.Date
FROM (SELECT R.Date,  SUM(G.Price) AS SumPrice
      FROM Goods G, Items I, Receipts R
      WHERE G.Id = I.Item AND R.ReceiptNumber = I.Receipt
         AND R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
      GROUP BY R.Date) AS D
WHERE D.SumPrice =
   (SELECT MIN(SumPrice)
   FROM (SELECT R.Date,  SUM(G.Price) AS SumPrice
         FROM Goods G, Items I, Receipts R
         WHERE G.Id = I.Item AND R.ReceiptNumber = I.Receipt
            AND R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
         GROUP BY R.Date) AS D2);

-- Q6
SELECT C2.FirstName, C2.LastName, COUNT(*) AS TotalPurchases, MAX(R2.Date)
FROM Customers C2, Receipts R2
WHERE C2.Id NOT IN 
   (SELECT C.Id -- id of all customers who bought on highest day
   FROM (SELECT R.Date,  SUM(G.Price) AS SumPrice
         FROM Goods G, Items I, Receipts R
         WHERE G.Id = I.Item AND R.ReceiptNumber = I.Receipt
            AND R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
         GROUP BY R.Date) DatePrice,
         Receipts R, Customers C
   WHERE DatePrice.SumPrice =
      (SELECT MAX(SumPrice) -- highest price of all the days
      FROM (SELECT R.Date,  SUM(G.Price) AS SumPrice -- list of dates + price
            FROM Goods G, Items I, Receipts R
            WHERE G.Id = I.Item AND R.ReceiptNumber = I.Receipt
               AND R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
            GROUP BY R.Date) AS DatePrice2)
      AND R.CustomerId = C.Id AND R.Date = DatePrice.Date)
   AND C2.Id = R2.CustomerId
GROUP BY C2.Id
ORDER BY TotalPurchases;


-- Q7
SELECT G.Flavor, G.Food, C.FirstName, C.LastName,  G.MaxPurchases
FROM (SELECT P.Food, P.Flavor, MAX(NumPurchases) AS MaxPurchases
      FROM (SELECT G.Food, G.Flavor, R.CustomerId,
               COUNT(I.Receipt) AS NumPurchases
            FROM Items I, Receipts R, Goods G
            WHERE I.Receipt = R.ReceiptNumber
               AND G.Id = I.Item AND G.Food = 'Cake'
               AND R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
            GROUP BY G.Id, R.CustomerId) AS P
      GROUP BY P.Flavor) G,
      (SELECT G.Food, G.Flavor, R.CustomerId,
         COUNT(I.Receipt) AS NumPurchases
      FROM Items I, Receipts R, Goods G
      WHERE I.Receipt = R.ReceiptNumber
         AND G.Id = I.Item AND G.Food = 'Cake'
         AND R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
      GROUP BY G.Id, R.CustomerId) AS P2,
      Customers C
WHERE P2.NumPurchases = G.MaxPurchases AND C.Id = P2.CustomerId
   AND P2.Flavor = G.Flavor
ORDER BY G.MaxPurchases DESC, C.LastName;

-- Q8
SELECT C.FirstName, C.LastName
FROM Customers C
WHERE C.Id NOT IN 
   (SELECT DISTINCT C.Id
   FROM Customers C, Receipts R
   WHERE R.Date >= '2007-10-5' AND R.Date <= '2007-10-11'
      AND R.CustomerId = C.Id )
ORDER BY C.LastName;

-- Q9
SELECT DISTINCT C3.FirstName, C3.LastName, R3.Date
FROM (SELECT C.Id, R.Date, COUNT(*) AS NumPurchases
      FROM Customers C, Receipts R
      WHERE C.Id = R.CustomerId
         AND R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
      GROUP BY C.Id, R.Date) AS C1,
      (SELECT C.Id, MAX(R.Date) AS MaxDate
      FROM Customers C, Receipts R
      WHERE C.Id = R.CustomerId
         AND R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
      GROUP BY C.Id) AS C2,
      Customers C3, Receipts R3,
      (SELECT C.Id, MIN(R.Date) AS MinDate
      FROM Customers C, Receipts R
      WHERE C.Id = R.CustomerId
         AND R.Date >= '2007-10-1' AND R.Date <= '2007-10-31'
      GROUP BY C.Id) AS C4
WHERE C1.Id = C2.Id AND C1.Date = C2.MaxDate AND NumPurchases > 1
   AND C3.Id = C1.Id AND R3.CustomerId = C3.Id
   AND R3.Date = C4.MinDate AND C4.Id = C3.Id
ORDER BY R3.Date;

-- Q10
SELECT G.Flavor, G.Food
FROM Goods G
WHERE G.Food = 'Cake' AND G.Flavor NOT IN
   (SELECT G.Flavor
   FROM Receipts R, Items I, Goods G
   WHERE R.ReceiptNumber = I.Receipt AND I.Item = G.Id
      AND DAYNAME(R.Date) = 'Wednesday' AND G.Food = 'Cake')
ORDER BY G.Flavor;
