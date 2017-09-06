import asyncio
import pycountry
import pyprind
import sys
import random
import aiofiles
from faker import Faker


class BColors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


faker_supported_locales = (
    'bg_BG', 'cs_CZ', 'de_DE', 'dk_DK',
    'el_GR', 'en_AU', 'en_CA', 'en_GB',
    'en_US', 'es_ES', 'et_EE', 'fa_IR',
    'fi_FI', 'fr_FR', 'hi_IN', 'hr_HR',
    'hu_HU', 'it_IT', 'ja_JP', 'ko_KR',
    'lt_LT', 'lv_LV', 'ne_NP', 'nl_NL',
    'no_NO', 'pl_PL', 'pt_BR', 'pt_PT',
    'ru_RU', 'sl_SI', 'sv_SE', 'tr_TR',
    'uk_UA', 'zh_CN', 'zh_TW'
)


class Serial:
    def __init__(self, default=0):
        self.id = default

    def increment(self, default=1):
        self.id += default
        return self.id


class User:
    identifier = Serial()

    def __init__(self):
        self.fake = Faker(random.choice(faker_supported_locales))
        self.id = self.identifier.increment()
        self.first_name = self.fake.first_name()
        self.last_name = self.fake.last_name()
        self.email = (self.first_name + '_' + self.last_name).lower() + '@' + self.fake.free_email_domain()
        self.birth_date = self.fake.date_time_between(start_date='-90y', end_date='-18y')

    def __str__(self):
        return str(self.id) + '\t' + str(self.email) + '\t' + str(self.first_name) + '\t' + str(
            self.last_name) + '\t' + str(self.birth_date)


class Location:
    identifier = Serial()

    def __init__(self):
        self.id = self.identifier.increment()
        while True:
            try:
                self.country = random.choice(list(pycountry.countries))
                self.place = random.choice(list(pycountry.subdivisions.get(country_code=self.country.alpha_2)))
                self.currency = pycountry.currencies.get(numeric=self.country.numeric)
                break
            except Exception:
                continue

    def __str__(self):
        return str(self.id) + '\t' + str(self.country.name) + '\t' + str(self.place.name) + '\t' + str(
            self.currency.name)


class Visit:
    identifier = Serial()

    def __init__(self):
        self.id = self.identifier.increment()
        self.fake = Faker()
        self.visited_at = self.fake.date_time_between(start_date='-20y', end_date='now')
        self.days_spent = self.fake.random_int(min=1, max=70)

    def __str__(self):
        return str(self.id) + '\t' + str(self.visited_at) + '\t' + str(self.days_spent)


async def generate_users(amount):
    async with aiofiles.open('users.txt', 'w') as f:
        bar = pyprind.ProgBar(amount, stream=sys.stdout)
        for i in range(amount):
            await f.write(str(User()) + '\n')
            bar.update()
        await f.flush()


async def generate_locations(amount):
    async with aiofiles.open('locations.txt', 'w') as f:
        bar = pyprind.ProgBar(amount, stream=sys.stdout)
        for i in range(amount):
            await f.write(str(Location()) + '\n')
            bar.update()
        await f.flush()


async def generate_visits(amount):
    async with aiofiles.open('visits.txt', 'w') as f:
        bar = pyprind.ProgBar(amount, stream=sys.stdout)
        for i in range(amount):
            await f.write(str(Visit()) + '\n')
            bar.update()
        await f.flush()


async def main():
    print(BColors.ENDC + 'Generating users...' + BColors.OKGREEN)
    await generate_users(amount=1000)
    print(BColors.ENDC + 'Generating locations...' + BColors.OKGREEN)
    await generate_locations(amount=1000)
    print(BColors.ENDC + 'Generating visits...' + BColors.OKGREEN)
    await generate_visits(amount=10000)
    print(BColors.ENDC + 'All done!')


if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
