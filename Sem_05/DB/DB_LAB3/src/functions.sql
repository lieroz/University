use Supply
GO

--  1. Скалярная функция --
CREATE FUNCTION dbo.AverageSize (@SUM int, @COUNT int)
RETURNS int
WITH RETURNS NULL ON NULL INPUT
AS BEGIN
	RETURN @SUM/@COUNT
END;
GO

SELECT [Type], Color, dbo.AverageSize(SUM(Size), COUNT(Size)) As 'AverageSize'
FROM Wear
GROUP BY [Type], Color

SELECT *
FROM Wear
WHERE [Type] = 'Куртка' and Color = 'Белый'

DROP FUNCTION dbo.AverageSize
GO

-- 2. Подставляемая таблиная функция--
CREATE FUNCTION dbo.FullSupply(@COUNT int)
RETURNS TABLE
AS
RETURN (SELECT TOP (@COUNT) s.WearNo, s.ShopNo, s.StorageNo, w.[Type], w.[Color], st.[Type] as 'Type of storage', [Count]
		FROM Supply AS s
			INNER JOIN Wear as w ON s.WearNo = w.WearNo
			INNER JOIN Shops as sh ON sh.ShopNo = s.ShopNo
			INNER JOIN Storages as st ON st.StorageNo = s.StorageNo
			)
GO

SELECT *
FROM dbo.FullSupply(50)
ORDER BY  [Count] DESC, [Type of storage] 

--DROP FUNCTION dbo.FullSupply
GO

-- 3. Многооператорная табличная функция--
CREATE FUNCTION dbo.FillSupplyTable(@COUNT int)
RETURNS @SupTable TABLE 
			(
				[WearNo] [int] NOT NULL,
				[ShopNo] [int] NOT NULL,
				[StorageNo] [int] NOT NULL,
				[Type] [nvarchar] (50) NOT NULL,
				[Color] [nvarchar] (50) NOT NULL,
				[Type of Storage] [char](20) NULL,
				[Count] [int] NOT NULL
			)			
AS BEGIN
	INSERT @SupTable (WearNo, ShopNo, StorageNo, [Type], Color, [Type of storage], [Count])
	(
	 SELECT *
	 FROM dbo.FullSupply(@COUNT)
	)
RETURN 
END
GO

SELECT * FROM dbo.FillSupplyTable(10)

DROP FUNCTION dbo.FillSupplyTable
GO

--4. Рекурсивная функция --
CREATE FUNCTION dbo.Fibon (@COUNT int)
RETURNS int
WITH RETURNS NULL ON NULL INPUT
AS
BEGIN
	if @COUNT = 1 OR @COUNT = 2
	BEGIN
		RETURN 1
	END
	RETURN (SELECT dbo.Fibon(@COUNT - 1) + (SELECT dbo.Fibon(@COUNT - 2)))
END;
GO

SELECT dbo.Fibon(12)

DROP FUNCTION dbo.Fibon