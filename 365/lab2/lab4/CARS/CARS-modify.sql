-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- CARS-modify.sql

-- keep in table vehicles made in 1979 and after w/ accel 13-14
DELETE FROM CarsData 
   WHERE  NOT((Year >= 1979 AND Accelerate >= 13 AND Accelerate <= 14)
      OR  (MPG >= 26 AND Horsepower > 110)) OR MPG IS NULL;
      
SELECT * FROM CarsData ORDER BY Year, Id;

-- Remove all attributes except car id, car, year, acceleration, mpg, number of cylinders, HP
ALTER TABLE CarsData
   DROP Edispl,
   DROP Weight;

-- Remove all cars with fewer than 5 cylinders
DELETE FROM CarsData
   WHERE Cylinders < 5;
   
SELECT * FROM CarsData ORDER BY Year, Id;
