USE Supply

ALTER TABLE [dbo].[Shops] ADD
	CONSTRAINT [PK_Shops] PRIMARY KEY (ShopNo)

ALTER TABLE [dbo].[Storages] ADD
	CONSTRAINT [PK_Storages] PRIMARY KEY (StorageNo)

ALTER TABLE [dbo].[Wear] ADD
	CONSTRAINT [PK_Wear] PRIMARY KEY (WearNo)

ALTER TABLE [dbo].[Supply] ADD
	CONSTRAINT [PK_Supply] PRIMARY KEY ([ShopNo], [WearNo], [StorageNo]),
	CONSTRAINT [FK_Supply_Shops] FOREIGN KEY(ShopNo) REFERENCES [Shops](ShopNo),
	CONSTRAINT [FK_Supply_Wear] FOREIGN KEY(WearNo) REFERENCES [Wear](WearNo),
	CONSTRAINT [FK_Supply_Storages] FOREIGN KEY(StorageNo) REFERENCES [Storages](StorageNo)

ALTER TABLE [dbo].[Storages] ADD
	CONSTRAINT [Type_check] CHECK ([Type] IN ('A','A-','B+','B','C','D'))

ALTER TABLE [dbo].[Wear] ADD
	CONSTRAINT [Size_check] CHECK (Size BETWEEN 30 AND 60)
GO

CREATE RULE [dbo].[HouseNo_rule]
AS
	@HouseNO > 0
GO

EXEC sp_bindrule 'HouseNO_rule', 'dbo.Shops.HouseNo'
EXEC sp_bindrule 'HouseNO_rule', 'dbo.Storages.HouseNo'
GO

