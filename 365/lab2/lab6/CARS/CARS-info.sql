-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- CARS-info.sql

-- Q1
SELECT CarMakers.FullName
FROM Countries, CarMakers
WHERE Countries.CountryName = 'japan'
   AND Countries.CountryId = CarMakers.Country
ORDER BY CarMakers.FullName;

-- Q2
SELECT DISTINCT CarsData.Year
FROM CarsData, CarNames
WHERE CarNames.Model = 'fiat' AND CarNames.MakeId = CarsData.Id
ORDER BY CarsData.Year;

-- Q3
SELECT CarNames.MakeDescription AS 'Car Name', 
   CarsData.Year, CarsData.Horsepower, CarsData.MPG
FROM CarsData, CarNames
WHERE CarNames.Model = 'volkswagen' AND CarNames.MakeId = CarsData.Id
   AND CarsData.Year >= 1980 AND CarsData.Year <= 1982
ORDER BY CarsData.Horsepower DESC;

-- Q4
SELECT CarNames.MakeDescription AS 'Car Name', CarMakers.FullName AS 'Maker'
FROM CarsData, CarNames, CarMakers, ModelList
WHERE CarsData.Id = CarNames.MakeId 
   AND CarNames.Model = ModelList.Model AND ModelList.Maker = CarMakers.Id
   AND CarsData.Cylinders !=4 AND CarsData.Year = 1979 
   AND CarsData.MPG > 20 AND CarsData.Accelerate < 15;
   
-- Q5
SELECT Names.MakeDescription AS 'Full Name', Data.Year,
  Data.Weight/Data.Horsepower AS Ratio
FROM Countries, CarsData Data, CarNames Names, ModelList, CarMakers
WHERE Data.Id = Names.MakeId AND Names.Model = ModelList.Model
   AND ModelList.Maker = CarMakers.Id
   AND CarMakers.Country = Countries.CountryId
   AND Countries.CountryName = 'france'
   AND Data.Year >= 1975 AND Data.Year <= 1978
ORDER BY Ratio DESC;