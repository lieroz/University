BULK INSERT Travels.dbo.users
FROM '/home/lieroz/University/Sem_05/DbCourse/Lab_01/users.txt'
WITH ( FIELDTERMINATOR = '\t', ROWTERMINATOR = '0x0a');

BULK INSERT Travels.dbo.locations
FROM '/home/lieroz/University/Sem_05/DbCourse/Lab_01/locations.txt'
WITH ( FIELDTERMINATOR = '\t', ROWTERMINATOR = '0x0a');

BULK INSERT Travels.dbo.visits
FROM '/home/lieroz/University/Sem_05/DbCourse/Lab_01/visits.txt'
WITH ( FIELDTERMINATOR = '\t', ROWTERMINATOR = '0x0a');

BULK INSERT Travels.dbo.ulv
FROM '/home/lieroz/University/Sem_05/DbCourse/Lab_01/associative.txt'
WITH ( FIELDTERMINATOR = '\t', ROWTERMINATOR = '0x0a');