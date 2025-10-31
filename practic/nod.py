'''# Задание 1
def nod(a,b):
    if b ==0:
        return abs(a)
    return nod(b, a % b)

def fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fib(n-1) + fib(n-2)
    
def r_num(n):
    if n < 10:
        return n
    else:
        last = n % 10
        b = n // 10
        return last *(10**len(str(b))) + r_num(b)

print(nod(48,18))

for i in range(15):
    print(f"F({i})={fib(i)}")

print(r_num(1234))
'''
# Задание 2
# 1. Рекурсивная функция для представления числа n в виде суммы m слагаемых
def sum_representations(m, n, current=None, start=1):
    """
    Выводит все различные представления числа n в виде суммы m натуральных слагаемых.
    Представления, различающиеся лишь порядком слагаемых, считаются одинаковыми.
    """
    if current is None:
        current = []
    
    if m == 1:
        if n >= start:
            print(current + [n])
        return
    
    for i in range(start, n - m + 2):
        sum_representations(m - 1, n - i, current + [i], i)

# 1. Рекурсивная функция для вычисления n!!
def double_factorial(n):
    """Вычисляет n!! (двойной факториал)"""
    if n <= 1:
        return 1
    return n * double_factorial(n - 2)


# 2. Рекурсивная функция для подсчета единиц в двоичном представлении
def count_ones_binary(n):
    """Определяет количество единиц в двоичном представлении натурального числа"""
    if n == 0:
        return 0
    return (n % 2) + count_ones_binary(n // 2)


# 3. Функция сложения двух чисел, используя только прибавление единицы
def add_with_increment(a, b):
    """Сложение двух чисел, используя только прибавление единицы"""
    if b == 0:
        return a
    return add_with_increment(a + 1, b - 1)


# 4. Функция умножения двух чисел, используя только операцию сложения
def multiply_with_addition(a, b):
    """Умножение двух чисел, используя только операцию сложения"""
    if b == 0:
        return 0
    return a + multiply_with_addition(a, b - 1)


# 5. Проверка, является ли фрагмент строки палиндромом
def is_palindrome(s, i, j):
    """Проверяет, является ли фрагмент строки с i-го по j-й символ палиндромом"""
    if i >= j:
        return True
    if s[i] != s[j]:
        return False
    return is_palindrome(s, i + 1, j - 1)


# 6. Подсчет количества цифр в заданном числе
def count_digits(n):
    """Подсчитывает количество цифр в заданном числе"""
    if abs(n) < 10:
        return 1
    return 1 + count_digits(n // 10)


# Демонстрация работы всех функций
if __name__ == "__main__":
    print("1. Представления числа 6 в виде суммы 3 слагаемых:")
    sum_representations(3, 6)
    
    print(f"\n1. Двойной факториал 7!! = {double_factorial(7)}")
    print(f"1. Двойной факториал 8!! = {double_factorial(8)}")
    
    print(f"\n2. Количество единиц в двоичном представлении 13: {count_ones_binary(13)}")
    
    print(f"\n3. Сложение 5 + 3 = {add_with_increment(5, 3)}")
    
    print(f"\n4. Умножение 4 * 3 = {multiply_with_addition(4, 3)}")
    
    test_string = "радар"
    print(f"\n5. Строка '{test_string}' является палиндромом: {is_palindrome(test_string, 0, len(test_string)-1)}")
    
    test_number = 12345
    print(f"\n6. Количество цифр в числе {test_number}: {count_digits(test_number)}")