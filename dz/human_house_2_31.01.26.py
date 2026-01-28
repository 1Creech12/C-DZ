class House:
    def __init__(self, area, price):
        self.area = area
        self.price = price
    
    def __str__(self):
        return f"Дом площадью {self.area}м², стоимостью {self.price}$"

class SmallHouse(House):
    def __init__(self, price=50000):
        super().__init__(area=40, price=price)

class Human:
    default_name = "Неизвестно"
    default_age = 0
    
    @classmethod
    def default_info(cls):
        print(f"Дефолтное имя: {cls.default_name}, дефолтный возраст: {cls.default_age}")
    
    def __init__(self, name=default_name, age=default_age):
        self.name = name
        self.age = age
        self.__money = 0
        self.__house = None
    
    def info(self):
        house_info = f"Дом площадью {self.__house.area}м²" if self.__house else "Нет дома"
        print(f"Имя: {self.name}")
        print(f"Возраст: {self.age}")
        print(f"Деньги: {self.__money}$")
        print(f"Дом: {house_info}")
    
    def earn_money(self, amount):
        self.__money += amount
        print(f"{self.name} заработал {amount}$. Теперь у него {self.__money}$")
    
    def __make_deal(self, house):
        self.__money -= house.price
        self.__house = house
        print(f"{self.name} купил дом площадью {house.area}м² за {house.price}$")
    
    def buy_house(self, house):
        if self.__money >= house.price:
            self.__make_deal(house)
        else:
            print(f"Недостаточно денег! У {self.name} есть {self.__money}$, а дом стоит {house.price}$")

print("1. Справочная информация о классе Human:")
Human.default_info()
print()

print("2. Создаем объект класса Human:")
person = Human("Иван", 30)
print(f"Создан человек: {person.name}, {person.age} лет")
print()

print("3. Информация о человеке:")
person.info()
print()

print("4. Создаем объект класса SmallHouse:")
small_house = SmallHouse()
print(small_house)
print()

print("5. Пытаемся купить дом:")
person.buy_house(small_house)
print()

print("6. Зарабатываем деньги:")
person.earn_money(60000)
print()

print("7. Снова пытаемся купить дом:")
person.buy_house(small_house)
print()

print("8. Финальное состояние человека:")
person.info()