-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- CARS-lab5.sql

-- Q1
SELECT N1.MakeDescription AS 'Full Name', D1.Year, Make.FullName
FROM CarsData D1, CarsData D2, CarNames N1, CarNames N2,
   ModelList Model, CarMakers Make
WHERE D1.Id = N1.MakeId AND D2.Id = N2.MakeId
   AND D1.Year = 1978 AND D1.MPG > D2.MPG
   AND D2.Year = 1982 AND N2.MakeDescription = 'honda civic'
   AND Model.Model = N1.Model AND Model.Maker = Make.Id
ORDER BY D1.MPG DESC;

-- Q2
SELECT AVG(D.Accelerate), MAX(D.Accelerate), MIN(D.Accelerate)
FROM CarsData D, CarNames N, ModelList Model, CarMakers Make, Countries
WHERE D.Id = N.MakeId AND N.Model = Model.Model 
   AND Model.Maker = Make.Id AND Make.Country = Countries.CountryId
   AND D.Cylinders = 8 AND D.Year >= 1971 AND D.Year <= 1976
   AND Countries.CountryName = 'usa';

-- Q3
SELECT COUNT(*)
FROM CarsData D1, CarsData D2, CarNames N1, CarNames N2
WHERE D1.Id = N1.MakeId AND D2.Id = N2.MakeId
   AND D1.Year = 1973 AND D1.Accelerate < D2.Accelerate
   AND D2.Year = 1979 AND N2.MakeDescription = 'fiat strada custom';
   
-- Q4
SELECT COUNT(DISTINCT Make.Id) AS '# Manufacturers produce > 4000 lbs'
FROM CarsData D, CarNames N, ModelList Model, CarMakers Make
WHERE D.Id = N.MakeId AND N.Model = Model.Model AND Model.Maker = Make.Id
   AND D.Weight > 4000;
   
-- Q5
SELECT D1.Year, AVG(D1.Weight/D1.Horsepower) AS 'Avg Weight-to-HP'
FROM CarsData D1
WHERE D1.Year = 1970

UNION

SELECT D2.Year, AVG(D2.Weight/D2.Horsepower) AS 'Avg Weight-to-HP'
FROM CarsData D2
WHERE D2.Year = 1971
ORDER BY Year;
 
