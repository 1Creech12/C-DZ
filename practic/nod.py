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
def number_representations(n, m, c=None, start=1):
    if c is None:
        c = []

    if m == 1:
        if n >= start:
            print(c + [n])
        return
    
    for i in range(start, n - m + 2):
        number_representations(n - i, m - 1, c + [i], i)

print("Представления числа 5 в виде суммы 3 слагаемых:")
number_representations(5, 3)
print("\n")


def nn(n):
    if n <= 0:
        return 1
    if n <= 2:
        return n
    return n * nn(n - 2)

print(f"7!! = {nn(7)}")
print(f"8!! = {nn(8)}")
print("\n")


def count_ones_binary(n):
    if n == 0:
        return 0
    return (n % 2) + count_ones_binary(n // 2)

number = 13
print(f"Количество единиц в двоичном представлении {number}: {count_ones_binary(number)}")
print("\n")


def recursive_add(a, b):
    if b == 0:
        return a
    return recursive_add(a + 1, b - 1)

print(f"5 + 3 = {recursive_add(5, 3)}")
print("\n")


def recursive_multiply(a, b):
    if b == 0:
        return 0
    if b == 1:
        return a
    return a + recursive_multiply(a, b - 1)

print(f"4 * 5 = {recursive_multiply(4, 5)}")
print("\n")


def is_palindrome_substring(s, i, j):
    if i >= j:
        return True
    if s[i] != s[j]:
        return False
    return is_palindrome_substring(s, i + 1, j - 1)

text = "радар"
print(f"Строка '{text}' является палиндромом: {is_palindrome_substring(text, 0, len(text)-1)}")

text2 = "программирование"
print(f"Фрагмент 'грам' является палиндромом: {is_palindrome_substring(text2, 3, 6)}")
print("\n")


def count_digits(n):
    if n < 10:
        return 1
    return 1 + count_digits(n // 10)

number = 12345
print(f"Количество цифр в числе {number}: {count_digits(number)}")
print("\n")