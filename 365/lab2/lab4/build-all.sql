--
--  CSC 365: build all databases
--

-- AIRLINES

-- set echo on
source AIRLINES/AIRLINES-setup.sql
-- set echo off
source AIRLINES/AIRLINES-insert.sql

-- BAKERY
-- set echo on
source BAKERY/BAKERY-setup.sql
-- set echo off
source BAKERY/BAKERY-insert.sql


-- CARS
-- set echo on
source CARS/CARS-setup.sql
-- set echo off
source CARS/CARS-insert.sql


-- CSU
-- set echo on
source CSU/CSU-setup.sql
-- set echo off
source CSU/CSU-insert.sql

-- INN
-- set echo on
source INN/INN-setup.sql
-- set echo off
source INN/INN-insert.sql

-- MARATHON
-- set echo on
source MARATHON/MARATHON-setup.sql
-- set echo off
source MARATHON/MARATHON-insert.sql

-- STUDENTS
-- set echo on
source STUDENTS/STUDENTS-setup.sql
-- set echo off
source STUDENTS/STUDENTS-insert.sql

-- WINE
-- set echo on
source WINE/WINE-setup.sql
-- set echo off
source WINE/WINE-insert.sql


-- KATZENJAMMER

source KATZENJAMMER/KATZENJAMMER-setup.sql
source KATZENJAMMER/KATZENJAMMER-insert.sql




source AIRLINES/AIRLINES-test.sql
source BAKERY/BAKERY-test.sql
source CARS/CARS-test.sql
source CSU/CSU-test.sql
source INN/INN-test.sql
source MARATHON/MARATHON-test.sql
source STUDENTS/STUDENTS-test.sql
source WINE/WINE-test.sql
source KATZENJAMMER/KATZENJAMMER-test.sql


source AIRLINES/AIRLINES-info.sql
source BAKERY/BAKERY-info.sql
source CARS/CARS-info.sql
source CSU/CSU-info.sql
source INN/INN-info.sql
source MARATHON/MARATHON-info.sql
source STUDENTS/STUDENTS-info.sql
source WINE/WINE-info.sql
source KATZENJAMMER/KATZENJAMMER-info.sql


show tables;

source clean-all.sql

-- set echo on
-- done








