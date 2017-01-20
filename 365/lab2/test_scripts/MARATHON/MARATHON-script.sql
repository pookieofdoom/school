-- MARATHON
-- set echo on
source MARATHON/MARATHON-setup.sql
SHOW TABLES;
-- set echo off
source MARATHON/MARATHON-build-marathon.sql

source MARATHON/MARATHON-test.sql
source MARATHON/MARATHON-info.sql
source MARATHON/MARATHON-cleanup.sql
SHOW TABLES