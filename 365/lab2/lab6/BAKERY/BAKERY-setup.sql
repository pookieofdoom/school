-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- BAKERY-setup.sql

-- DROP TABLE IF EXISTS Items, Receipts, Customers, Goods;

CREATE TABLE Goods(
   Id VARCHAR(15),
   Flavor VARCHAR(15),
   Food VARCHAR(15),
   Price FLOAT,
   PRIMARY KEY (Id),
   UNIQUE (Flavor, Food)
   );
   
CREATE TABLE Customers(
   Id INT,
   LastName VARCHAR(15),
   FirstName VARCHAR(15),
   PRIMARY KEY (Id)
   );
   
CREATE TABLE Receipts(
   ReceiptNumber INT,
   Date DATE,
   CustomerId INT,
   PRIMARY KEY (ReceiptNumber),
   FOREIGN KEY (CustomerId) REFERENCES Customers(Id)
   );
   
CREATE TABLE Items(
   Receipt INT,
   Ordinal INT,
   Item VARCHAR(15),
   PRIMARY KEY (Receipt, Ordinal),
   FOREIGN KEY (Receipt) REFERENCES Receipts(ReceiptNumber),
   FOREIGN KEY (Item) REFERENCES Goods(Id)
   );
