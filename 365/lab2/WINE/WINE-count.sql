-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- WINE-count.sql

-- Q1
SELECT Score, AVG(Price), MIN(Price), MAX(Price),
   COUNT(*) AS 'Total # Wines', SUM(Cases)
FROM Wine 
   WHERE Score > 88
GROUP BY Score
ORDER BY Score;

-- Q2
SELECT W.Year, COUNT(*)
FROM Wine W, Appellations A, Grapes G
WHERE G.Color = 'White' AND W.Grape = G.Grape
   AND A.County = 'Santa Barbara' AND W.Appellation = A.Appellation
   AND W.Score >= 90
GROUP BY W.Year
ORDER BY W.Year;

-- Q3
SELECT W.Appellation, A.County,
   COUNT(*), AVG(W.Price), 12 * SUM(DISTINCT W.Cases)
FROM Wine W, Appellations A
WHERE W.Year = 2007 AND W.Grape = 'Cabernet Sauvingnon'
   AND W.Appellation = A.Appellation
GROUP BY W.Appellation
HAVING COUNT(*) > 2
ORDER BY COUNT(DISTINCT W.No) DESC;

-- Q4
SELECT W.Appellation, SUM(W.Cases * 12 * W.Price) AS TotalSales
FROM Wine W, Appellations A
WHERE W.Appellation = A.Appellation
   AND W.Year = 2008 AND A.Area = 'Central Coast'
GROUP BY W.Appellation
ORDER BY TotalSales DESC;

-- Q5
SELECT A.County, MAX(W.Score)
FROM Appellations A, Wine W, Grapes G
WHERE G.Color = 'Red' AND W.Grape = G.Grape
   AND W.Year = 2009 AND W.Appellation = A.Appellation
   AND A.County != 'N/A'
GROUP BY A.County
ORDER BY MAX(W.Score) DESC;
