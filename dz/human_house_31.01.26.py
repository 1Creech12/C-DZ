class Human:
    default_name = "Иван"
    default_age = 30
    
    def __init__(self, name=default_name, age=default_age):
        self.name = name
        self.age = age
        
        self.__money = 0
        self.__house = None
    
    def info(self):
        # Вывод информации о человеке
        print(f"Имя: {self.name}")
        print(f"Возраст: {self.age}")
        print(f"Деньги: {self.__money}")
        print(f"Дом: {self.__house}")
    
    @staticmethod
    def default_info():
        print(f"Имя по умолчанию: {Human.default_name}")
        print(f"Возраст по умолчанию: {Human.default_age}")
    
    def __make_deal(self, house, price):
        self.__money -= price
        self.__house = house
    
    def earn_money(self, amount):
        # Увеличение количества денег
        self.__money += amount
        print(f"Заработано {amount} денег. Текущий баланс: {self.__money}")
    
    def buy_house(self, house, discount=0):
        # Покупка дома со скидкой
        final_price = house.final_price(discount)
        
        if self.__money >= final_price:
            self.__make_deal(house, final_price)
            print(f"Дом успешно куплен за {final_price}!")
        else:
            print(f"Недостаточно денег для покупки дома. Нужно: {final_price}, есть: {self.__money}")


class House:
    def __init__(self, area, price):
        self._area = area
        self._price = price
    
    def final_price(self, discount):
        return self._price * (100 - discount) / 100
    
    def __str__(self):
        return f"Дом площадью {self._area} м², цена: {self._price}"

if __name__ == "__main__":
    print("1. Значения по умолчанию:")
    Human.default_info()
    print()
    
    person = Human("Алексей", 25)
    person.earn_money(50000)
    print()
    
    house1 = House(100, 40000)
    print(f"2. Создан дом: {house1}")
    
    print("\n3. Попытка покупки дома:")
    person.buy_house(house1)
    
    print("\n4. Зарабатываем дополнительные деньги:")
    person.earn_money(10000)
    
    print("\n5. Покупка дома со скидкой 10%:")
    person.buy_house(house1, 10)
    
    print("\n6. Итоговая информация о человеке:")
    person.info()