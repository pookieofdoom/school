-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- WINE-lab5.sql

-- Q1
SELECT W.Grape, W.Winery, W.Name, W.Score, W.Price * W.Cases * 12 AS Revenue
FROM Wine W, Wine W2, Appellations A
WHERE W.Appellation = A.Appellation AND A.County = 'Napa' AND W.Year = 2006
   AND W2.Year = 2006 AND W2.Name = 'Appelation Series'
   AND W2.Appellation = 'Paso Robles' AND W2.Grape = 'Zinfandel' 
   AND W2.Winery = 'Rosenblum'
   AND (W.Price * W.Cases * 12) > (W2.Price * W2.Cases * 12)
ORDER BY Revenue;

-- Q2
SELECT W.*
FROM Wine W, Wine Tor
WHERE Tor.Grape = 'Chardonnay' AND Tor.Winery = 'Tor'
   AND W.Year = Tor.Year 
   AND W.Score > Tor.Score AND W.Cases > Tor.Cases;

-- Q3
SELECT AVG(W.Score) AS 'Avg Score of Sonoma Country Syrah'
FROM Wine W, Appellations A
WHERE A.County = 'Sonoma'
   AND A.Appellation = W.Appellation AND W.Grape = 'Syrah';

-- Q4
SELECT Grapes.Color, SUM(Red.Price * Red.Cases * 12) AS 'Total Rev'
FROM Wine Red, Grapes, Appellations A
WHERE Grapes.Color = 'Red' AND Red.Grape = Grapes.Grape 
   AND A.County = 'Santa Barbara' AND Red.Year = 2008
   AND Red.Appellation = A.Appellation

UNION

SELECT Grapes.Color, SUM(White.Price * White.Cases * 12) AS 'Total Rev'
FROM Wine White, Grapes, Appellations A
WHERE Grapes.Color = 'White' AND White.Grape = Grapes.Grape 
   AND A.County = 'Santa Barbara' AND White.Year = 2008
   AND White.Appellation = A.Appellation;

-- Q5
SELECT AVG(W.Cases)
FROM Wine W, Appellations A
WHERE W.Appellation = A.Appellation AND A.Area = 'Central Coast'
   AND W.Grape = 'Pinot Noir';

-- Q6
SELECT COUNT(*) AS 'Overall # of different red wines'
FROM Wine W, Grapes G, Wine W2
WHERE G.Color = 'Red' AND G.Grape = W.Grape
   AND W.Appellation = 'Russian River Valley'
   AND W.Year = W2.Year
   AND W2.Score = 98 AND W.Appellation = W2.Appellation;

-- Q7
SELECT COUNT(*) AS 'Total # of Zinfandel '
FROM Wine W1, Wine W2
WHERE W1.Grape = 'Zinfandel' AND W2.Grape = 'Grenache'
   AND W2.Score = 97
   AND (W1.Price * W1.Cases * 12) > (W2.Price * W2.Cases * 12);

 
