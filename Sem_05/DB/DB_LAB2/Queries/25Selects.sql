USE Supply

--1. Использование предиката сравнения--
SELECT *
FROM Wear
WHERE Size > 40
ORDER BY Size DESC

--2. Предикат BETWEEN --
SELECT Name, Street, HouseNo
FROM Shops
WHERE City = 'Рязань' AND Street = 'Гагарина' AND HouseNo BETWEEN '1' AND '70'
ORDER BY HouseNo ASC

--3. Предикат LIKE--
SELECT [Type], Country, Material, Size, Color, Supply.ShopNo, Supply.StorageNo, Supply.[Count]
FROM Wear JOIN Supply ON Wear.WearNo = Supply.WearNo
WHERE Color LIKE '%евый%' 

--4. Предикат IN с вложенным подзапросом--
SELECT *
FROM Wear As w 
WHERE w.WearNo IN
	(
		SELECT WearNo
		FROM Supply
		WHERE Count > 90
	)	

--5. Предикат EXISTS с вложенным подзапросом--
SELECT *
FROM Supply AS otable
WHERE EXISTS
	 (
		SELECT *
		FROM Storages AS itable
		WHERE [Type] = 'A' and itable.StorageNo = otable.StorageNo
	 )
ORDER BY StorageNo

--6. Предикат сравнения с квантором--
SELECT *
FROM Storages
WHERE HouseNo > ALL
	(
		SELECT HouseNo
		FROM Storages
		WHERE City = 'Москва'
	) 


--7.Инструкция SELECT, использующая агрегатные функции в выражениях столбцов. --
SELECT AVG(Size) AS 'Average Size', MAX(Size) AS 'Max Size',
SUM(Size)/ COUNT(Size) AS 'Calculated Average'
FROM Wear
Where [type] = 'Куртка' and Color = 'Синий'

-- 8.Инструкция SELECT, использующая скалярные подзапросы в выражениях столбцов.--
SELECT *, 
	(
		SELECT Avg(Size)
		FROM Wear
		WHERE [type] =  
			( SELECT [type]
				FROM Wear
				WHERE Wear.WearNo = Supply.WearNo
			)

	) As 'Average Size'
FROM Supply
WHERE [Count] > 70		

--9.Инструкция SELECT, использующая простое выражение CASE. --
SELECT Name, COUNT(Name) AS 'Count of shops',
	CASE Name
		WHEN 'Mexx' THEN 'Good wear'
		WHEN 'Твоё' THEN 'Worse shop'
		WHEN 'Uniclo' THEN 'Качестевеные штаны и куртки'
 	END AS 'Note'
FROM Shops
GROUP BY Name
ORDER BY [Note] DESC

--10. Поисковое выражение CASE--
SELECT [Type], Country, Material, Size,
	CASE
		WHEN Size <= 42 THEN 'S'
		WHEN Size BETWEEN 43 AND 46 THEN 'M'
		WHEN Size BETWEEN 47 AND 50 THEN 'L'
		ELSE 'XL'
	END AS NewSize
FROM Wear
ORDER BY Size

--11.Создание новой временной локальной таблицы из результирующего набора данных инструкции SELECT. --
SELECT  City, COUNT(Street) AS 'Count of Storages', MIN([Type]) AS 'Best Type', MAX([type]) AS 'Worst Type'
INTO CitysStoragesInfo
FROM Storages
WHERE [Type] IS NOT NULL
GROUP BY City
ORDER BY [Count of Storages] DESC

/*
SELECT *
FROM CitysStoragesInfo

DROP TABLE CitysStoragesInfo
*/


--12.Инструкция SELECT, использующая вложенные коррелированные подзапросы в качестве производных таблиц в предложении FROM.--
--13.Инструкция SELECT, использующая вложенные подзапросы с уровнем вложенности 3.--
SELECT *
FROM Supply
WHERE StorageNo IN
(
	SELECT StorageNo
	FROM Storages
	WHERE City IN
	(
		Select City
		FROM (
				SELECT TOP 5 City, COUNT(City) As 'Count'
				FROM Shops
				WHERE Name = 'InCity'
				GROUP BY City
		    	ORDER BY [Count] DESC
			 ) AS CityShop
	)
)

SELECT Name, City
FROM Shops
ORDER BY Name

--14.Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY, но без предложения HAVING.--
SELECT  City, Street, COUNT(Street) AS 'Count of Storages', MIN([Type]) AS 'Best Type', MAX([type]) AS 'Worst Type'
FROM Storages
WHERE [Type] IS NOT NULL
GROUP BY City, Street
ORDER BY City, [Count of Storages]

--15.Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY и  предложения HAVING.--
SELECT  City, Street, COUNT(Street) AS 'Count of Storages', MIN([Type]) AS 'Best Type', MAX([type]) AS 'Worst Type'
FROM Storages
WHERE [Type] IS NOT NULL
GROUP BY City, Street
HAVING MAX([Type]) < 'D'
ORDER BY City, [Count of Storages]

--16. Однострочная инструкция INSERT--
INSERT Storages (Name, City, Street, HouseNo) 
VALUES ('CoCoCompany', 'Ижевск', 'Чугунная', 11)

SELECT *
FROM Storages

--17.	Многострочная инструкция INSERT, выполняющая вставку в таблицу результирующего набора данных вложенного подзапроса.-- 
INSERT Storages (Name, City, Street, HouseNo)
SELECT ('CoCoCompany'), City, Street, HouseNo
FROM Shops
WHERE City = 'Москва' and Name = 'Mexx'

 --18. Простая инструкция UPDATE --
 UPDATE Storages
 SET [Type] = 'C'
 WHERE [Type] is NULL

 --19.Инструкция UPDATE со скалярным подзапросом в предложении SET. --
UPDATE Shops
SET HouseNo = 
	(
		SELECT MIN(HouseNo)
		FROM Shops
		WHERE City = 'Волгоград' AND Name = 'Mexx' AND Street = 'Гагарина'
	)
WHERE City = 'Волгоград' AND Name = 'Mexx' AND Street = 'Гагарина'


SELECT *
FROM Shops
WHERE Name = 'Mexx' And City = 'Волгоград' AND Street = 'Гагарина'

 --20. Простая инструкция delete--
 DELETE Storages
 WHERE City = 'Ижевск'

 DELETE Storages
 WHERE StorageNo > 1000

 --21.Инструкция DELETE с вложенным коррелированным подзапросом в предложении WHERE.--
 DELETE FROM Supply
 WHERE StorageNo IN
	(
		Select DISTINCT Storages.StorageNo
		FROM Storages JOIN Supply ON Storages.StorageNo = Supply.StorageNo
		WHERE City = 'Астрахань'
	)
GO

 --22.Инструкция SELECT, использующая простое обобщенное табличное выражение.--
 WITH NewWear ([Type], CountWear)
 AS
 (
	SELECT [Type], Count(*) As CountWear
	FROM Wear
	WHERE Color = 'Черный'
	GROUP BY [Type]
 )
 SELECT AVG(CountWear) AS 'Среднее количество вещей черного цвета'
 FROM NewWear

 --23.Инструкция SELECT, использующая рекурсивное обобщенное табличное выражение.--

 /*Создание таблицы вещей Wear3*/
DROP TABLE Wear3
 
CREATE TABLE [dbo].[Wear3](
	[WearNo] [int] IDENTITY(1,1) NOT NULL,
	[Type] [nvarchar](20) NOT NULL,
	[Country] [nvarchar](50) NOT NULL,
	[Material] [nvarchar](50) NOT NULL,
	[BonusNo] [int] NULL  /* номер вещи, с которой идет в подарок*/
	CONSTRAINT PK_Wear3 PRIMARY KEY CLUSTERED (WearNo ASC) 
)
GO

INSERT Wear3 ([Type], Country, Material, BonusNo)
VALUES
('Куртка', 'Россия', 'Хлопок', NULL),
('Куртка', 'Турция', 'Полиэстер', 1),
('Шорты', 'Франция', 'Акрил', 2),
('Футболка', 'Индия', 'Акрил', 2),
('Рубашка', 'Россия', 'Хлопок', 4),
('Брюки', 'Испания', 'Шерсть', 2),
('Рубашка', 'Франция', 'Акрил', 3),
('Рубашка', 'Франция', 'Хлопок', 3)
GO

-- Определение ОТВ
WITH BonusTable(WearBonus, WearNo, [Type], Material, Level)
AS
(
-- Определение закрепленного элемента
SELECT w.BonusNo, w.WearNo, w.[Type], w.Material, 0 AS Level
FROM Wear3 AS w
WHERE BonusNo IS NULL
UNION ALL
-- Определение рекурсивного элемента
SELECT w.BonusNo, w.WearNo, w.[Type], w.Material, Level + 1
FROM Wear3 AS w INNER JOIN BonusTable AS b ON w.BonusNo = b.WearNo
)
-- Инструкция, использующая ОТВ
SELECT WearBonus, WearNo, [Type], Material, Level
FROM BonusTable ;
GO

SELECT *
FROM Wear3


 --24. Использование оператор PIVOT--

SELECT [Type], [52], [50], [48]
FROM 
(
	SELECT [Type], Size
	FROM Wear
) as SourceT
PIVOT 
(
	Count(Size) for Size in ([52], [50], [48])
) AS MaxLargeTable


 --25. Инструкция MERGE--
 -- Создаем таблицу Wear2 и синхронизируем ее с таблицей Wear1
SELECT *
INTO Wear2
FROM Wear
GO

--DROP TABLE Wear2

SELECT *
FROM Wear2

UPDATE Wear2
SET Color = 'Хаки'
WHERE WearNo BETWEEN 950 AND 1000

INSERT Wear2 ([Type], Country, Material, Size, Color)
VALUES
('Куртка', 'Россия', 'Акрил', 52, 'Синий'),
('Куртка', 'Россия', 'Акрил', 52, 'Красный')

MERGE Wear2
USING Wear
ON (Wear2.WearNo = Wear.WearNo)
WHEN MATCHED  THEN
	UPDATE SET Wear2.Color = Wear.Color
WHEN NOT MATCHED BY SOURCE THEN
	DELETE;  /*Удаляем строки из таблицы при несовпадении ключей */

DROP TABLE Wear2


