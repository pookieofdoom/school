-- BAKERY
-- set echo on
source BAKERY/BAKERY-setup.sql
SHOW TABLES;
-- set echo off
source BAKERY/BAKERY-build-goods.sql
source BAKERY/BAKERY-build-customers.sql
source BAKERY/BAKERY-build-receipts.sql
source BAKERY/BAKERY-build-items.sql
source BAKERY/BAKERY-test.sql
-- source BAKERY/BAKERY-modify.sql
-- source BAKERY/BAKERY-info.sql
source BAKERY/BAKERY-lab5.sql
source BAKERY/BAKERY-cleanup.sql
SHOW TABLES;