-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- BAKERY-info.sql

-- Q1
SELECT Flavor, Food, Price
FROM Goods
WHERE Food = 'Cake'
ORDER BY Price DESC;

-- Q2
SELECT Flavor, Food, Price
FROM Goods
WHERE (Flavor = 'Chocolate' AND Price >= 1.00 And Price <= 2.00)
   OR Food = 'Meringue' OR  (Food = 'Eclair' AND Flavor != 'Vanilla')
ORDER BY Flavor, Food;

-- Q3
SELECT G.Flavor, G.Food, G.Price
FROM Customers C, Receipts R, Goods G, Items I
WHERE C.LastName = 'ARZT' AND C.FirstName = 'TERRELL'
   AND C.Id = R.CustomerId
   AND R.Date = '2007/10/13' 
   AND R.ReceiptNumber = I.Receipt
   AND I.Item = G.Id
ORDER BY G.Food, G.Flavor;

-- Q4
SELECT DISTINCT G.Flavor, G.Food
FROM Receipts R, Items I, Goods G
WHERE R.Date = '2007/10/4' 
   AND R.ReceiptNumber = I.Receipt 
   AND I.Item  = G.Id
   AND G.Food = 'Eclair'
ORDER BY G.Flavor;

-- Q5
SELECT D.Food, D.Flavor, D.Price
FROM Customers C, Receipts R, Goods G, Items I, Goods D
WHERE C.LastName = 'SOPKO' AND C.FirstName = 'RAYFORD'
   AND R.Date = '2007/10/27'
   AND C.Id = R.CustomerId
   AND R.ReceiptNumber = I.Receipt
   AND I.Item = G.Id
   AND D.Price < G.Price
ORDER BY D.Price DESC;