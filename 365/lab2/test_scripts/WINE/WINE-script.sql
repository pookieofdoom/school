-- set echo on
source WINE/WINE-setup.sql
show tables;
-- set echo off


source WINE/WINE-build-grapes.sql

source WINE/WINE-build-appellations.sql

source WINE/WINE-build-wine.sql

source WINE/WINE-test.sql

-- source WINE/WINE-modify.sql

-- source WINE/WINE-info.sql
source WINE/WINE-lab5.sql
source WINE/WINE-cleanup.sql
show tables;

