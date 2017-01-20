CREATE TABLE musicians(
  MId INT, Name VARCHAR(30), BandId INT, From_Year INT, To_Year INT, PRIMARY KEY (MId), FOREIGN KEY (BandId) REFERENCES bands(Id));

INSERT INTO musicians VALUES 
  (1, 'Roger Waters', 1, 1966, 1983),
  (2, 'Syd Barrett', 1, 1966, 1968),
  (3, 'Robert Fripp', 2, 1969, 2002),
  (4, 'Adrian Belew', 2, 1981, 2002),
  (5, 'Irmin Schmidt', 3, 1968, 1978),
  (6, 'Michael Karoli', 3, 1968, 1978),
  (7, 'Jim Morrison', 4, 1967, 1971),
  (8, 'Lou Reed', 5, 1967, 1973),
  (9, 'Daevid Allen', 6, 1969, 1974),
  (10, 'Pierre Moerlen', 6, 1975, 1978),
  (11, 'Jon Anderson', 7, 1968, 1981),
  (12, 'Bill Bruford', 7, 1968, 1972),
  (13, 'Bill Bruford', 2, 1972, 2010);