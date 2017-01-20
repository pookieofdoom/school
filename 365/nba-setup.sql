CREATE TABLE Players(
     ID INT,
     FirstName VARCHAR(16),
     LastName VARCHAR(16),
     TeamID INT,
     Position INT,  
     Height INT,
     Weight INT,
     ShootingHand CHAR(1),
     PRIMARY KEY (Id),
     FOREIGN KEY (TeamId) REFERENCES Teams(ID),
     FOREIGN KEY (Position) REFERENCES Positions(Pos)
   );
   
CREATE TABLE Positions(
   Pos INT,
   Position VARCHAR(16)
   );

CREATE TABLE Teams(
   ID INT,
   Name VARCHAR(12),
   State CHAR(2),
   City VARCHAR(16),
   CoachID INT,
   Abbrev VARCHAR(3),
   PRIMARY KEY (ID),
   FOREIGN KEY (CoachId) REFERENCES Coaches(Id)
   );

CREATE TABLE Coaches(
   ID INT,
   FirstName VARCHAR(16),
   LastName VARCHAR(16),
   PRIMARY KEY (Id)
   );
   
CREATE TABLE Stats(
   PlayerId INT,
   Season INT,
   Age INT,
   TeamId INT,
   Points INT, 
   Assists INT,
   Rebounds INT,
   Steals INT,
   Blocks INT,
   FGM INT,
   FGA INT,
   3PM INT,
   3PA INT,
   FTM INT,
   FTA INT,
   TurnOver INT,
   PRIMARY KEY(PlayerId, Season, TeamId),
   FOREIGN KEY(PlayerId) REFERENCES Players(ID),
   FOREIGN KEY(TeamId) REFERENCES Teams(ID)
   );

