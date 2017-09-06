import asyncio
import pycountry
import pyprind
import sys
import random
import aiofiles
from faker import Faker
from faker.config import AVAILABLE_LOCALES


class BColors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


class Serial:
    def __init__(self, default=0):
        self.id = default

    def increment(self, default=1):
        self.id += default
        return self.id


class User:
    identifier = Serial()
    names = []

    def __init__(self):
        self.fake = Faker(random.choice(list(AVAILABLE_LOCALES)))
        self.id = self.identifier.increment()
        while True:
            self.first_name = self.fake.first_name()
            self.last_name = self.fake.last_name()
            if self.first_name + ' ' + self.last_name in self.names:
                continue
            else:
                break
        self.names.append(self.first_name + ' ' + self.last_name)
        self.email = (self.first_name + '_' + self.last_name).lower() + '@' + self.fake.free_email_domain()
        self.birth_date = self.fake.date_time_between(start_date='-90y', end_date='-18y')

    def __str__(self):
        return str(self.id) + '\t' + str(self.email) + '\t' + str(self.first_name) + '\t' + str(
            self.last_name) + '\t' + str(self.birth_date) + '\t'


class Location:
    identifier = Serial()
    locations = []

    def __init__(self):
        self.id = self.identifier.increment()
        while True:
            try:
                self.country = random.choice(list(pycountry.countries))
                self.place = random.choice(list(pycountry.subdivisions.get(country_code=self.country.alpha_2)))
                self.currency = pycountry.currencies.get(numeric=self.country.numeric)
            except Exception:
                continue
            if self.country.name + ' ' + self.place.name in self.locations:
                continue
            else:
                break
        self.locations.append(self.country.name + ' ' + self.place.name)

    def __str__(self):
        return str(self.id) + '\t' + str(self.country.name) + '\t' + str(self.place.name) + '\t' + str(
            self.currency.name)


class Visit:
    identifier = Serial()

    def __init__(self):
        self.fake = Faker()
        self.id = self.identifier.increment()
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


async def generate_associative_data(users, locations, visits):
    fake = Faker()
    async with aiofiles.open('associative.txt', 'w') as f:
        bar = pyprind.ProgBar(visits, stream=sys.stdout)
        for i in range(visits):
            await f.write(
                str(fake.random_int(min=1, max=users)) + '\t' + str(fake.random_int(min=1, max=locations)) + '\t' + str(
                    i + 1) + '\t' + str(fake.random_int(min=1, max=10)) + '\n')
            bar.update()
        await f.flush()


USERS, LOCATIONS, VISITS = 1000, 1000, 10000


async def main():
    print(BColors.ENDC + 'Generating users...' + BColors.OKGREEN)
    await generate_users(amount=USERS)
    print(BColors.ENDC + 'Generating locations...' + BColors.OKGREEN)
    await generate_locations(amount=LOCATIONS)
    print(BColors.ENDC + 'Generating visits...' + BColors.OKGREEN)
    await generate_visits(amount=VISITS)
    print(BColors.ENDC + 'Generating associative...' + BColors.OKGREEN)
    await generate_associative_data(users=USERS, locations=LOCATIONS, visits=VISITS)
    print(BColors.ENDC + 'All done!')


if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
