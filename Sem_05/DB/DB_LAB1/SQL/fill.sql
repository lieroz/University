USE Supply

BULK INSERT Shops
FROM 'C:\Users\akama\Desktop\Базы Данных\DB_LAB1\DataGenerator\DataGenerator\shops.txt'
WITH(CODEPAGE = 'ACP', DATAFILETYPE = 'widechar', FIELDTERMINATOR = ' ', ROWTERMINATOR = '\n');

BULK INSERT Storages
FROM 'C:\Users\akama\Desktop\Базы Данных\DB_LAB1\DataGenerator\DataGenerator\storages.txt'
WITH(CODEPAGE = 'ACP', DATAFILETYPE = 'widechar', FIELDTERMINATOR = ' ', ROWTERMINATOR = '\n');

BULK INSERT Wear
FROM 'C:\Users\akama\Desktop\Базы Данных\DB_LAB1\DataGenerator\DataGenerator\clothes.txt'
WITH(CODEPAGE = 'ACP', DATAFILETYPE = 'widechar', FIELDTERMINATOR = ' ', ROWTERMINATOR = '\n');

BULK INSERT Supply
FROM 'C:\Users\akama\Desktop\Базы Данных\DB_LAB1\DataGenerator\DataGenerator\scs.txt'
WITH(CODEPAGE = 'ACP', DATAFILETYPE = 'char', FIELDTERMINATOR = ' ', ROWTERMINATOR = '\n');

GO