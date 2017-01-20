-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- CARS-count.sql

-- Q1
SELECT CM.Maker, MAX(Data.Weight), AVG(Data.Horsepower)
FROM CarMakers CM, Countries, CarsData Data, CarNames Names, ModelList M
WHERE Countries.CountryName = 'japan' AND CM.Country = Countries.CountryId
   AND M.Maker = CM.Id AND Names.Model = M.Model AND Data.Id = Names.MakeId
GROUP BY CM.Maker
ORDER BY CM.Maker;

-- Q2
SELECT CM.Maker, COUNT(*)
FROM CarMakers CM, Countries, CarsData Data, CarNames Names, ModelList M
WHERE Countries.CountryName = 'usa' AND CM.Country = Countries.CountryId
   AND M.Maker = CM.Id AND Names.Model = M.Model AND Data.Id = Names.MakeId
   AND Data.Cylinders = 4 AND Data.Weight < 4000 AND Data.Accelerate < 14
GROUP BY CM.Maker
ORDER BY COUNT(*) DESC;

-- Q3
SELECT Data3.Year, MAX(Data3.MPG), MIN(Data3.MPG), AVG(Data3.MPG)
FROM CarMakers CM1, CarNames N1, CarNames N2, ModelList M1,
   CarsData Data1, CarsData Data2, CarMakers CM2, CarNames N,
   ModelList M2, CarsData Data3
WHERE CM1.Maker = 'toyota' AND CM1.Id = M1.Maker AND N1.Model = M1.Model
   AND N2.Model = M1.Model AND N1.MakeId != N2.MakeId AND N1.MakeId = Data1.Id
   AND N2.MakeId = Data2.Id AND Data1.Year = Data2.Year
   AND CM2.Maker = 'honda' AND CM2.Id = M2.Maker AND M2.Model = N.Model
   AND N.MakeId = Data3.Id AND Data3.Year = Data1.Year
GROUP BY Data3.Year;
ORDER BY Data3.Year;

-- Q4
SELECT Data.Year, MAX(Data.Edispl), MIN(Data.Edispl)
FROM CarMakers CM, Countries, CarsData Data, CarNames Names, ModelList M
WHERE Countries.CountryName = 'usa' AND CM.Country = Countries.CountryId
   AND M.Maker = CM.Id AND Names.Model = M.Model AND Data.Id = Names.MakeId
GROUP BY Data.Year
HAVING AVG(Data.Horsepower) < 100
ORDER BY Data.Year;

-- Q5
SELECT Data.Year, 
   AVG(Data.Weight / Data.Horsepower * Data.MPG * Data.Accelerate) AS QRating
FROM CarMakers CM, Countries, CarsData Data, CarNames Names, ModelList M
WHERE Countries.CountryName = 'usa' AND CM.Country = Countries.CountryId
   AND M.Maker = CM.Id AND Names.Model = M.Model AND Data.Id = Names.MakeId
GROUP BY Data.Year
ORDER BY Data.Year;

