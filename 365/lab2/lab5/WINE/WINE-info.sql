-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- WINE-info.sql

-- Q1
SELECT Appellation AS 'AVA'
FROM Appellations
WHERE County = 'Santa Barbara' AND isAVA = 'Yes'
ORDER BY Appellation;

-- Q2
SELECT Other.Grape, Other.Name, Other.Year, Other.Score
FROM Wine Viognier, Wine Other
WHERE Viognier.Grape = 'Viognier'
  AND Viognier.Winery = Other.Winery
  AND Other.Grape != 'Viognier'
ORDER BY Other.Year, Other.Name;

-- Q3
SELECT Winery, Name, Price, Score, Cases, 
  ((20 * (Score - 88) + 10) / Price) * 1200. / Cases AS 'Collector Rating'
FROM Wine
WHERE Grape = 'Grenache' AND Year = 2008
ORDER BY 'Collector Rating' DESC;

-- Q4
SELECT DISTINCT Wine.Year AS 'Vintage Years'
FROM Appellations, Wine
WHERE Appellations.Appellation = Wine.Appellation 
   AND Appellations.County = 'Sonoma'
   AND Wine.Grape = 'Zinfandel' AND Wine.Score > 92
ORDER BY Wine.Year;

-- Q5
SELECT Winery, Name, Year AS 'Vintage', Score,
   (Price * 12 * Cases) AS 'Total Revenue'
FROM Wine
WHERE Grape = 'Cabernet Sauvingnon' AND Score >= 96
ORDER BY 'Total Revenue' DESC;

-- Q6
SELECT Kosta.Price + 2 * Darioush.Price + Kistler.Price AS 'Total Price'
FROM Wine Kosta, Wine Darioush, Wine Kistler
WHERE Kosta.Winery = 'Kosta Browne' AND Kosta.Name = 'Koplen Vineyard'
   AND Kosta.Year = 2008 AND Kosta.Grape = 'Pinot Noir'
   AND Darioush.Winery = 'Darioush' AND Darioush.Year = 2007 
   AND Darioush.Name = 'Darius II' AND Darioush.Grape = 'Cabernet Sauvingnon'
   AND Kistler.Name = 'McCrea Vineyard' AND Kistler.Winery = 'Kistler' 
   AND Kistler.Year = 2006 AND Kistler.Grape = 'Chardonnay';
