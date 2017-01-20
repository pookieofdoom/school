-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- CARS-queries.sql

-- Q1
SELECT C.MakeDescription, C.Year
FROM (SELECT D.MPG, N.MakeDescription, D.Year
      FROM CarsData D, CarNames N
      WHERE D.Id = N.MakeId
      GROUP BY D.MPG) AS C
WHERE C.MPG = 
   (SELECT MAX(C2.MPG)
   FROM (SELECT D.MPG, N.MakeDescription
         FROM CarsData D, CarNames N
         WHERE D.Id = N.MakeId
         GROUP BY D.MPG) AS C2);

-- Q2 
SELECT C.MakeDescription, C.Year
FROM (SELECT D.Accelerate, D.Year, N.MakeDescription, D.Weight
      FROM CarsData D, CarNames N
      WHERE D.Id = N.MakeId
         AND D.Accelerate =
            (SELECT MIN(Accelerate)
            FROM CarsData)) AS C
WHERE C.Weight = 
   (SELECT MAX(D.Weight)
   FROM CarsData D, CarNames N
   WHERE D.Id = N.MakeId
      AND D.Accelerate =
         (SELECT MIN(Accelerate)
         FROM CarsData));

-- Q3
SELECT MaxCountry.CountryName, P.Maker
FROM (SELECT CM.Maker, Countries.CountryName, COUNT(*) AS NumCars
      FROM CarsData D, CarNames N, ModelList ML, CarMakers CM, Countries
      WHERE D.Id = N.MakeId AND N.Model = ML.Model AND ML.Maker = CM.Id
         AND CM.Country = Countries.CountryId
      GROUP BY CM.Maker) AS P,
      (SELECT P2.CountryName, MAX(NumCars) AS MaxCars
      FROM (SELECT CM.Maker, Countries.CountryName, COUNT(*) AS NumCars
            FROM CarsData D, CarNames N, ModelList ML, CarMakers CM, Countries
            WHERE D.Id = N.MakeId AND N.Model = ML.Model AND ML.Maker = CM.Id
               AND CM.Country = Countries.CountryId
            GROUP BY CM.Maker) AS P2
      GROUP BY P2.CountryName) AS MaxCountry
WHERE MaxCountry.CountryName = P.CountryName
   AND P.NumCars = MaxCountry.MaxCars
ORDER BY MaxCountry.CountryName;

-- Q4
SELECT P.Year, P.FullName, C.NumCars, Q.MinAccel
FROM (SELECT D.Year, CM.Id, CM.FullName,  AVG(D.Accelerate) AS AvgAccel
      FROM CarsData D, CarNames N, ModelList ML, CarMakers CM
      WHERE D.Id = N.MakeId AND N.Model = ML.Model AND ML.Maker = CM.Id
      GROUP BY D.Year, CM.Id) AS P, -- could be CM.Maker  or N.Model?
      
      (SELECT P2.Year, MIN(P2.AvgAccel) AS MinAccel
      FROM (SELECT D.Year, N.Model, CM.FullName,  AVG(D.Accelerate) AS AvgAccel
            FROM CarsData D, CarNames N, ModelList ML, CarMakers CM
            WHERE D.Id = N.MakeId AND N.Model = ML.Model AND ML.Maker = CM.Id
            GROUP BY D.Year, CM.Id) AS P2 -- could be CM.Maker
      GROUP BY P2.Year) AS Q,
      
      (SELECT D.Year, CM.Id, COUNT(*) AS NumCars
      FROM CarsData D, CarNames N, ModelList ML, CarMakers CM
      WHERE D.Id = N.MakeId AND N.Model = ML.Model AND ML.Maker = CM.Id
      GROUP BY D.Year, CM.Id) AS C -- should it be model and not id?
WHERE P.Year = Q.Year AND C.Id = P.Id AND C.Year = P.Year
   AND P.AvgAccel = Q.MinAccel
ORDER BY P.Year;

-- Q5
SELECT P.MakeDescription, P.Year, P.CountryName
FROM (SELECT N.MakeDescription, D.Year, Countries.CountryName, D.MPG
      FROM CarsData D, CarNames N, ModelList ML, CarMakers CM, Countries
      WHERE D.Id = N.MakeId AND N.Model = ML.Model AND ML.Maker = CM.Id
         AND CM.Country = Countries.CountryId AND D.Cylinders = 8) AS P
WHERE P.MPG =
         (SELECT MAX(D.MPG)
         FROM CarsData D
         WHERE D.Cylinders = 8);
         
-- Q6
SELECT MostFE.Best - LeastFE.Least
FROM (SELECT MAX(D.MPG) AS Best
      FROM CarsData D
      WHERE D.Cylinders = 8) AS MostFE,
      (SELECT MIN(D.MPG) AS Least
      FROM CarsData D
      WHERE D.Cylinders = 4) AS LeastFE;
      
-- Q7    
SELECT P.CountryName, P.MakeDescription, P.Year, P.Weight
FROM (SELECT Countries.CountryName, MAX(D.Weight) AS MaxWeight
      FROM CarsData D, CarNames N, ModelList ML, CarMakers CM, Countries
      WHERE D.Id = N.MakeId AND N.Model = ML.Model AND ML.Maker = CM.Id
         AND CM.Country = Countries.CountryId
         AND D.Accelerate < 
            (SELECT MAX(D.Accelerate) AS Best
            FROM CarsData D
            WHERE D.Cylinders = 8)
      GROUP BY Countries.CountryName) AS MaxWeightPerCountry,
      
      (SELECT Countries.CountryName, N.MakeDescription, D.Accelerate,
         D.Weight, D.Year
      FROM CarsData D, CarNames N, ModelList ML, CarMakers CM, Countries
      WHERE D.Id = N.MakeId AND N.Model = ML.Model AND ML.Maker = CM.Id
         AND CM.Country = Countries.CountryId
         AND D.Accelerate <
            (SELECT MAX(D.Accelerate) AS Best
            FROM CarsData D
            WHERE D.Cylinders = 8)
      ORDER BY Countries.CountryName, D.Weight) AS P
WHERE P.CountryName = MaxWeightPerCountry.CountryName 
   AND P.Weight = MaxWeightPerCountry.MaxWeight;
