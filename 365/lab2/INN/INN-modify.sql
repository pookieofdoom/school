-- Anthony Dinh
-- adinh03@calpoly.edu
-- CPE 365
-- INN-modify.sql

-- Add attr for description of room
ALTER TABLE Rooms
   ADD (Description VARCHAR(280));

UPDATE Rooms
   SET Description = "Come experience our long soft pillows! They offer great support and if you do not like it, then you can abscond!"
   WHERE RoomId = "AOB";
   
UPDATE Rooms
   SET Description = "We summon you to enjoy our traditional two king sized room. You will not regret this oppertunity and experience of a life time!"
   WHERE RoomId = "CAS";

UPDATE Rooms
   SET Description = "Do you want the best bang for your buck? Come relax in these apropos traditional king size beds! Perfect for those who want to spend money for the best experience"
   WHERE RoomId = "FNA";

UPDATE Rooms
   SET Description = "This room will foreshadow the good times with you and your significant other. This is perfect size for a couple with a single Queen sized bed. Do not let family and friends distract from this oppertunity!"
   WHERE RoomId = "HBB";

UPDATE Rooms
   SET Description = "This room has not changed ever since it was built! Enjoy this rustic decor room which gives a decorous feeling. You will be leaving feeling dignified and proud of your choices for staying here!"
   WHERE RoomId = "IBD";

UPDATE Rooms
   SET Description = "Sign up for this room if you want the best healthiest experience possible! Enjoy the view of the beach and in the mean time, sleep comfortably on our King sized bed!"
   WHERE RoomId = "IBS";

UPDATE Rooms
   SET Description = "We know how confusing it must be to sign up for rooms for your vaction, but we got you covered. This room is perfect for a family of four and the sign up is easy! After this experience, you will be begging to come back!"
   WHERE RoomId = "MWC";

UPDATE Rooms
   SET Description = "This room is perfect for singles. There is only one bed so you are not paying for wasted space! Defy all those couple rooms and come stay in this one instead!"
   WHERE RoomId = "RND";
   
UPDATE Rooms
   SET Description = "Do you like to sleep? Do you like an inexpensive room? Do you need lots of space? Come stay at this room and your experience will clear all your questions!"
   WHERE RoomId = "RTE";

UPDATE Rooms
   SET Description = "Come experience the most inexpensive but luxury room ever. This is perfect for singles and you can award yourself with extra treats for all the money you are saving!"
   WHERE RoomId = "TAA";

SELECT * FROM Rooms ORDER BY RoomId \G
