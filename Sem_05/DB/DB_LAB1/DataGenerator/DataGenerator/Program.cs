using System;
using System.Collections.Generic;
using System.IO;

namespace DataGenerator
{
	internal class Program
	{
		private static readonly List<string> companies = new List<string>
		{
			"DailyWear",
			"ABCGroup",
			"WWWear",
			"7FamilY",
			"Boris&Co",
			"Ivanofff"
		};

		private static readonly List<string> cities = new List<string>
		{
			"Калуга",
			"Москва",
			"Брянск",
			"Санкт-Петербург",
			"Рязань",
			"Казань",
			"Волгоград",
			"Уфа",
			"Астрахань",
			"Омск"
		};

		private static readonly List<string> streets = new List<string>
		{
			"Ленина",
			"Гагарина",
			"Кирова",
			"Первомайская",
			"Мира",
			"Пушкина",
			"Строителей",
			"Победы",
			"Советская",
			"Октябрьская"
		};

		private static readonly List<string> types = new List<string>
		{
			"A",
			"A-",
			"B+",
			"B",
			"C",
			"D"
		};

		private static readonly List<string> shops = new List<string>
		{
			"InCity",
			"Oggi",
			"Ostin",
			"Sela",
			"Zara",
			"Zarina",
			"Zolla",
			"Mexx",
			"Uniclo",
			"Твоё",
			"Familia",
			"Mango"
		};

		private static readonly List<string> countries = new List<string>
		{
			"Россия",
			"Беларусь",
			"Китай",
			"Индия",
			"Турция",
			"Испания",
			"Италия",
			"Вьетнам",
			"США",
			"Франция"
		};

		private static readonly List<string> clothes = new List<string>
		{
			"Пальто",
			"Футболка",
			"Джемпер",
			"Рубашка",
			"Свитер",
			"Кардиган",
			"Майка",
			"Плащ",
			"Куртка",
			"Брюки",
			"Юбка",
			"Шорты"
		};

		private static readonly List<string> materials = new List<string>
		{
			"Хлопок",
			"Лён",
			"Шерсть",
			"Акрил",
			"Ангора",
			"Шёлк",
			"Бамбук",
			"Кожа",
			"Полиэстер",
			"Эластан"
		};

		private static readonly List<string> colors = new List<string>
		{
			"Белый",
			"Черный",
			"Зеленый",
			"Красный",
			"Синий",
			"Желтый",
			"Оранжевый",
			"Серый",
			"Коричневый",
			"Розовый"
		};

		private static readonly Random random = new Random(DateTime.Now.Millisecond);

		public static T GetRandom<T>(IList<T> list)
		{
			return list[random.Next(0, list.Count)];
		}

		delegate void FileFormatDelegate(StreamWriter stream, string format, params object[] args);

		private const int DATA_COUNT = 1000;

		private static void Main()
		{
			var f1 = new StreamWriter("../../storages.txt");
			var f2 = new StreamWriter("../../clothes.txt");
			var f3 = new StreamWriter("../../shops.txt");
			var f4 = new StreamWriter("../../scs.txt");

			for (var i = 0; i < DATA_COUNT; i++)
			{
				FileFormatDelegate fileFormatDelegate;

				if (i != DATA_COUNT - 1)
				{
					fileFormatDelegate = (stream, format, args) => { stream.WriteLine(format, args); };
				}
				else
				{
					fileFormatDelegate = (stream, format, args) => { stream.Write(format, args); };
				}

				fileFormatDelegate(f1, "{0} {1} {2} {3} {4} {5}", i + 1, GetRandom(companies), GetRandom(cities),
					GetRandom(streets), random.Next(0, 100), GetRandom(types));
				fileFormatDelegate(f2, "{0} {1} {2} {3} {4} {5}", i + 1, GetRandom(clothes), GetRandom(countries),
					GetRandom(materials), (random.Next(0, 10) + 18) * 2, GetRandom(colors));
				fileFormatDelegate(f3, "{0} {1} {2} {3} {4}", i + 1, GetRandom(shops), GetRandom(cities), GetRandom(streets),
					random.Next(0, 100));
				fileFormatDelegate(f4, "{0} {1} {2} {3}", random.Next(0, 1000), random.Next(0, 1000), random.Next(0, 1000),
					random.Next(0, 100));
			}

			f1.Close();
			f2.Close();
			f3.Close();
			f4.Close();
		}
	}
}