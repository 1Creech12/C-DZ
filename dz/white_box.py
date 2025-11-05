import math

def triangle_type_by_angles(a, b, c):
    if a <= 0 or b <= 0 or c <= 0:
        return "Ошибка: все стороны должны быть положительными числами!"

    if a + b <= c or a + c <= b or b + c <= a:
        return "Ошибка: такие стороны не могут образовать треугольник!"

    sides = sorted([a, b, c])
    a2, b2, c2 = sides[0]**2, sides[1]**2, sides[2]**2
    
    p = (a + b + c) / 2
    area = math.sqrt(p * (p - a) * (p - b) * (p - c))

    if a == b == c:
        triangle_type = "Равносторонний треугольник"
    elif a == b or a == c or b == c:
        triangle_type = "Равнобедренный треугольник"
    else:
        triangle_type = "Разносторонний треугольник"

    if a2 + b2 > c2:
        triangle_type_2 = "Остроугольный треугольник"
    elif a2 + b2 < c2:
        triangle_type_2 = "Тупоугольный треугольник"
    else:
        triangle_type_2 = "Прямоугольный треугольник"
   
    p = (a + b + c) / 2
    area = math.sqrt(p * (p - a) * (p - b) * (p - c))
    
    return f"{triangle_type}, {triangle_type_2}, Площадь: {area:.2f}"

if __name__ == "__main__":
    try:
        a = float(input("Введите длину стороны A: "))
        b = float(input("Введите длину стороны B: "))
        c = float(input("Введите длину стороны C: "))
        
        result = triangle_type_by_angles(a, b, c)
        print(result)
    except ValueError:
        print("Ошибка: введите числовые значения!")