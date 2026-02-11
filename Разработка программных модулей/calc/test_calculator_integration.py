from calculator_with_history import CalculatorWithHistory
def test_addition_with_history():
    """Тест 1: Сложение и сохранение в истории"""
    # Создаем калькулятор с историей
    calc = CalculatorWithHistory()
    
    # Выполняем сложение
    result = calc.perform_addition(5, 3)
    
    # Проверяем результат
    assert result == 8, f"Ожидалось 8, получено {result}"
    
    # Получаем историю
    history = calc.get_operation_history()
    
    # Проверяем запись в истории
    assert len(history) == 1, f"Ожидалась 1 запись, получено {len(history)}"
    assert history[0] == "5 + 3 -> 8", f"Ожидалась '5 + 3 -> 8', получено '{history[0]}'"


def test_subtraction_with_history():
    """Тест 2: Вычитание и сохранение в истории"""
    calc = CalculatorWithHistory()
    
    # Выполняем вычитание
    result = calc.perform_subtraction(10, 4)
    
    # Проверяем результат
    assert result == 6, f"Ожидалось 6, получено {result}"
    
    # Получаем историю
    history = calc.get_operation_history()
    
    # Проверяем запись в истории
    assert len(history) == 1, f"Ожидалась 1 запись, получено {len(history)}"
    assert history[0] == "10 - 4 -> 6", f"Ожидалась '10 - 4 -> 6', получено '{history[0]}'"


def test_multiple_operations_history():
    """Тест 3: Несколько операций в истории"""
    calc = CalculatorWithHistory()
    
    # Выполняем две операции
    result1 = calc.perform_addition(1, 1)
    result2 = calc.perform_subtraction(5, 2)
    
    # Проверяем результаты операций
    assert result1 == 2, f"Ожидалось 2, получено {result1}"
    assert result2 == 3, f"Ожидалось 3, получено {result2}"
    
    # Получаем всю историю
    history = calc.get_operation_history()
    
    # Проверяем количество записей
    assert len(history) == 2, f"Ожидалось 2 записи, получено {len(history)}"
    
    # Проверяем порядок и содержание записей
    assert history[0] == "1 + 1 -> 2", f"Первая запись: ожидалось '1 + 1 -> 2', получено '{history[0]}'"
    assert history[1] == "5 - 2 -> 3", f"Вторая запись: ожидалось '5 - 2 -> 3', получено '{history[1]}'"