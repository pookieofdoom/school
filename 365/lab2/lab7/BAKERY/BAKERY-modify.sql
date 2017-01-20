-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- BAKERY-modify.sql

-- Have to remove foreign key before removing information from parent
ALTER TABLE Items
   DROP FOREIGN KEY Items_ibfk_2;

-- Remove all information about pasteries except for Cakes
DELETE FROM Goods
   WHERE NOT (Food = "Cake");

-- Increase the prices of chocolate and Opera Cake by 20%
UPDATE Goods
   SET Price = Price * 1.20
   WHERE Flavor = "Chocolate" OR Flavor = "Opera";

-- Reduce the prices of Lemon Cake and Napoleon Cake by $2
UPDATE Goods
   SET Price = Price - 2
   WHERE Flavor = "Lemon" OR Flavor = "Napoleon";

-- Reduce the price of all other cakes by 10%
UPDATE Goods
   SET Price = Price * .9
   WHERE Flavor != "Chocolate" AND Flavor != "Opera" AND Flavor != "Lemon" AND Flavor != "Napoleon";
   
SELECT * FROM Goods ORDER BY Id;
