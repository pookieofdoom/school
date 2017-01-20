-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- WINE-queries.sql

-- Q1
SELECT A.*
FROM (SELECT W.Grape, G.Color, COUNT(DISTINCT W.Appellation) AS NumApp
      FROM Wine W, Grapes G
      WHERE W.Grape = G.Grape
      GROUP BY W.Grape) AS A
WHERE A.NumApp =
   (SELECT MAX(A2.NumApp)
   FROM (SELECT W.Grape, G.Color, COUNT(DISTINCT W.Appellation) AS NumApp
         FROM Wine W, Grapes G
         WHERE W.Grape = G.Grape
         GROUP BY W.Grape) AS A2);
         
-- Q2
-- County or Appellation for Santa Barbara...??
SELECT A.Grape
FROM (SELECT W.Grape, G.Color, COUNT(*) AS NumWhite
      FROM Wine W, Grapes G, Appellations A
      WHERE W.Appellation = A.Appellation AND A.County = 'Santa Barbara'
         AND W.Grape = G.Grape AND G.Color = 'White'
      GROUP BY W.Grape) AS A
WHERE A.NumWhite = 
   (SELECT MAX(A2.NumWhite)
   FROM (SELECT W.Grape, G.Color, COUNT(*) AS NumWhite
         FROM Wine W, Grapes G, Appellations A
         WHERE W.Appellation = A.Appellation AND A.County = 'Santa Barbara'
            AND W.Grape = G.Grape AND G.Color = 'White'
         GROUP BY W.Grape) AS A2);
      
-- Q3
SELECT H.Grape
FROM (SELECT W.Grape, COUNT(*) AS NumHighScore
      FROM Wine W
      WHERE W.Score >= 93
      GROUP BY W.Grape) AS H
WHERE H.NumHighScore = 
   (SELECT MAX(H2.NumHighScore)
   FROM (SELECT W.Grape, COUNT(*) AS NumHighScore
         FROM Wine W
         WHERE W.Score >= 93
         GROUP BY W.Grape) AS H2);
         
-- Q4
SELECT H.Appellation
FROM (SELECT W.Appellation, COUNT(*) AS NumHighScore
      FROM Wine W
      WHERE W.Score >= 93
      GROUP BY W.Appellation) AS H
WHERE H.NumHighScore =
   (SELECT MAX(H2.NumHighScore)
   FROM (SELECT W.Appellation, COUNT(*) AS NumHighScore
         FROM Wine W
         WHERE W.Score >= 93
         GROUP BY W.Appellation) AS H2);
         
-- Q5
SELECT R.*
FROM (SELECT W.Year, W.Winery, W.Name, W.Score,
         W.Price * 12 * W.Cases AS Revenue
      FROM Wine W
      WHERE W.Score >= 93) AS R
WHERE R.Revenue = 
   (SELECT MAX(R2.Revenue)
   FROM (SELECT W.Year, W.Winery, W.Name, W.Score,
            W.Price * 12 * W.Cases AS Revenue
         FROM Wine W
         WHERE W.Score >= 93) AS R2);

-- Q6
SELECT W.Winery, W.Name, W.Appellation, W.Score, W.Price
FROM Wine W
WHERE W.Year = 2008 AND W.Grape = 'Zinfandel'
   AND W.Score >
   ALL(SELECT W.Score
      FROM Wine W
      WHERE W.Year = 2007 AND W.Grape = 'Grenache');
      
-- Q7
SELECT C.CarnerosWins, D.DCVWins
FROM (SELECT COUNT(DISTINCT W1.Year) AS CarnerosWins
      FROM Wine W1
      WHERE W1.Appellation = 'Carneros'
         AND W1.Year >= 2005 AND W1.Year <= 2009
         AND W1.Score >
         ALL(SELECT W2.Score
            FROM Wine W2
            WHERE W2.Appellation = 'Dry Creek Valley'
            AND W2.Year = W1.Year)
      ORDER BY W1.Year, W1.Score) AS C,
      
      (SELECT COUNT(DISTINCT W2.Year) AS DCVWins
      FROM Wine W2
      WHERE W2.Appellation = 'Dry Creek Valley'
         AND W2.Year >= 2005 AND W2.Year <= 2009
         AND W2.Score >
         ALL(SELECT W1.Score
            FROM Wine W1
            WHERE W1.Appellation = 'Carneros'
            AND W2.Year = W1.Year)
      ORDER BY W2.Year, W2.Score) AS D;

-- Q8
SELECT W.Cases
FROM Wine W
WHERE W.Price =
   (SELECT MAX(R.Price)
   FROM (SELECT W.Grape, W.Price
         FROM Wine W, Grapes G
         WHERE W.Grape = G.Grape AND G.Color = 'Red'
         GROUP BY W.Price) AS R);

-- Q9
SELECT A.Year, A.Appellation
FROM (SELECT W.Year, W.Appellation, W.Price
      FROM Wine W
      GROUP BY W.Year, W.Appellation, W.Price) AS A,
      
      (SELECT A.Year, MAX(A.Price) AS MaxPrice
      FROM (SELECT W.Year, W.Appellation, W.Price
            FROM Wine W
            GROUP BY W.Year, W.Appellation, W.Price) AS A
         GROUP BY A.Year) AS B
WHERE A.Price = B.MaxPrice AND A.Year = B.Year;
