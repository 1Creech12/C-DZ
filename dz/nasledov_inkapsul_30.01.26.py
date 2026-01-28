class LibraryItem:
    _id_counter = 1

    def __init__(self, title, author, year):
        self._title = title
        self._author = author
        self._year = year
        self.__item_id = LibraryItem._id_counter
        self.__is_checked_out = False
        LibraryItem._id_counter += 1

    # Геттеры
    def get_title(self):
        return self._title

    def get_author(self):
        return self._author

    def get_year(self):
        return self._year

    def get_item_id(self):
        return self.__item_id

    def get_is_checked_out(self):
        return self.__is_checked_out

    def set_is_checked_out(self, value):
        if isinstance(value, bool):
            self.__is_checked_out = value
        else:
            raise ValueError("Значение должно быть True или False")


class Book(LibraryItem):
    def __init__(self, title, author, year, genre, page_count):
        super().__init__(title, author, year)
        self.genre = genre
        self.__page_count = page_count

    def get_page_count(self):
        return self.__page_count

    def set_page_count(self, page_count):
        if page_count >= 1:
            self.__page_count = page_count
        else:
            raise ValueError("Количество страниц не может быть меньше 1")


class Magazine(LibraryItem):
    def __init__(self, title, author, year, issue_number):
        super().__init__(title, author, year)
        self._issue_number = issue_number

    def get_magazine_info(self):
        return f"Журнал: {self._title}, Выпуск: {self._issue_number}, Автор: {self._author}, Год: {self._year}"


class DVD(LibraryItem):
    VALID_RATINGS = {"G", "PG", "PG-13", "R", "NC-17"}

    def __init__(self, title, author, year, duration, rating):
        super().__init__(title, author, year)
        self.__duration = duration
        self.__rating = rating

    def get_duration(self):
        return self.__duration

    def set_duration(self, duration):
        if 1 <= duration <= 300:
            self.__duration = duration
        else:
            raise ValueError("Продолжительность должна быть от 1 до 300 минут")

    def get_rating(self):
        return self.__rating

    def set_rating(self, rating):
        if rating in DVD.VALID_RATINGS:
            self.__rating = rating
        else:
            raise ValueError(f"Рейтинг должен быть одним из: {DVD.VALID_RATINGS}")

if __name__ == "__main__":
    book1 = Book("Война и мир", "Лев Толстой", 1869, "Роман", 1225)
    print(f"Книга: {book1.get_title()}, Автор: {book1.get_author()}, ID: {book1.get_item_id()}")

    mag1 = Magazine("Наука и жизнь", "Редакция", 2023, 5)
    print(mag1.get_magazine_info())

    dvd1 = DVD("Интерстеллар", "Кристофер Нолан", 2014, 169, "PG-13")
    print(f"DVD: {dvd1.get_title()}, Рейтинг: {dvd1.get_rating()}, ID: {dvd1.get_item_id()}")