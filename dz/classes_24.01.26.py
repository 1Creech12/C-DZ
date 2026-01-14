# Класс Студент
class Student:
    def __init__(self, name, age, course, average_score, student_id):
        self.name = name
        self.age = age
        self.course = course
        self.average_score = average_score
        self.student_id = student_id
    
    def increase_course(self):
        if self.course < 5:
            self.course += 1
        else:
            print("Максимальный курс - 5")
    
    def update_average(self, new_gpa):
        if 0 <= new_gpa <= 5:
            self.gpa = new_gpa
        else:
            print("Средный балл должен быть от 0 до 5")
    
    def __str__(self):
        return f"{self.name}, курс {self.course}, Средний балл: {self.gpa}"

# Класс Книга
class Book:
    def __init__(self, title, author, year, number, pages):
        self.title = title
        self.author = author
        self.year = year
        self.number = number
        self.pages = pages
        self.is_available = True
    
    def borrow_book(self):
        if self.is_available:
            self.is_available = False
            print(f"Книга '{self.title}' взята")
        else:
            print(f"Книга '{self.title}' уже взята")
    
    def return_book(self):
        if not self.is_available:
            self.is_available = True
            print(f"Книга '{self.title}' возвращена")
        else:
            print(f"Книга '{self.title}' уже в библиотеке")
    
    def __str__(self):
        status = "доступна" if self.is_available else "взята"
        return f"'{self.title}' ({self.author}), {status}"

# Класс Автомобиль
class Car:
    def __init__(self, brand, model, year, color, price):
        self.brand = brand
        self.model = model
        self.year = year
        self.color = color
        self.price = price
        self.is_running = False
    
    def start_engine(self):
        if not self.is_running:
            self.is_running = True
            print(f"{self.brand} {self.model} заведен")
        else:
            print(f"{self.brand} {self.model} уже заведен")
    
    def stop_engine(self):
        if self.is_running:
            self.is_running = False
            print(f"{self.brand} {self.model} заглушен")
        else:
            print(f"{self.brand} {self.model} уже заглушен")
    
    def __str__(self):
        status = "заведен" if self.is_running else "заглушен"
        return f"{self.brand} {self.model} ({self.year}), {status}"

# Создание студентов
student1 = Student("Иван Петров", 19, 1, 4.2, "ST001")
student2 = Student("Мария Сидорова", 20, 2, 4.7, "ST002")

# Создание книг
book1 = Book("Преступление и наказание", "Фёдор Достоевский", 1866, "978-5-17-090879-1", 608)
book2 = Book("Мастер и Маргарита", "Михаил Булгаков", 1967, "978-5-389-06204-3", 480)

# Тестирование метода студентов
print("\tСтуденты")
print(f"До: {student1}")
student1.increase_course()
student1.update_average(4.5)
print(f"После: {student1}")

print(f"\nДо: {student2}")
student2.update_average(4.9)
student2.update_average(6.0) # неправильный балл
print(f"После: {student2}")

# Тестирование метода книг
print("\n\tКниги")
print(f"До: {book1}")
book1.borrow_book()
book1.return_book()
print(f"После: {book1}")

print(f"\nДо: {book2}")
book2.borrow_book()
book2.borrow_book()  # попытка взять уже взятую книгу
book2.return_book()
print(f"После: {book2}")

# Создание автомобилей
car1 = Car("Toyota", "Camry", 2020, "Серебристый", 25000)
car2 = Car("BMW", "X5", 2022, "Черный", 75000)

# Тестирование метода автомобилей
print("\n\tАвтомобили")
print(f"До: {car1}")
car1.start_engine()
car1.start_engine()  # попытка завести уже заведенный
car1.stop_engine()
print(f"После: {car1}")

print(f"\nДо: {car2}")
car2.start_engine()
car2.stop_engine()
car2.stop_engine()  # попытка заглушить уже заглушенный
print(f"После: {car2}")