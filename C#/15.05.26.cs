using System;

class Program
{
    static void Main()
    {
        // Задание 1
        try
        {
            Console.Write("Задание 1 \nВведите набор цифр (0-9): ");
            string input1 = Console.ReadLine();
            int num1 = ConvertToInt(input1);
            Console.WriteLine($"Результат: {num1}");
        }
        catch (FormatException ex) { Console.WriteLine($"Ошибка: {ex.Message}"); }
        catch (OverflowException ex) { Console.WriteLine($"Ошибка: {ex.Message}"); }

        // Задание 2
        try
        {
            Console.Write("Задание 2 \nВведите набор 0 и 1: ");
            string input2 = Console.ReadLine();
            int num2 = BinaryToInt(input2);
            Console.WriteLine($"Результат: {num2}");
        }
        catch (FormatException ex) { Console.WriteLine($"Ошибка: {ex.Message}"); }
        catch (OverflowException ex) { Console.WriteLine($"Ошибка: {ex.Message}"); }

        // Задание 3
        try
        {
            CreditCard card = new CreditCard("1234567812345678", "Иванов Абдул Васькович", 123, new DateTime(2025, 12, 31));
            Console.WriteLine("Задание 3 \nКарта создана успешно.");
        }
        catch (ArgumentException ex) { Console.WriteLine($"Ошибка: {ex.Message}"); }

        // Задание 4
        try
        {
            Console.Write("Задание 4 \nВведите выражение (например, 3*2*1*4): ");
            string input4 = Console.ReadLine();
            int result = EvaluateMultiplication(input4);
            Console.WriteLine($"Результат: {result}");
        }
        catch (FormatException ex) { Console.WriteLine($"Ошибка: {ex.Message}"); }
        catch (OverflowException ex) { Console.WriteLine($"Ошибка: {ex.Message}"); }
    }

    // Задание 1
    static int ConvertToInt(string input)
    {
        if (string.IsNullOrEmpty(input))
            throw new FormatException("Пустая строка");
        foreach (char c in input)
            if (c < '0' || c > '9')
                throw new FormatException("Строка должна содержать только цифры 0-9.");
        try { return int.Parse(input); }
        catch (OverflowException) { throw new OverflowException("Число выходит за границы типа int."); }
    }

    // Задание 2
    static int BinaryToInt(string input)
    {
        if (string.IsNullOrEmpty(input))
            throw new FormatException("Пустая строка");
        foreach (char c in input)
            if (c != '0' && c != '1')
                throw new FormatException("Строка должна содержать только 0 и 1.");
        try { return Convert.ToInt32(input, 2); }
        catch (OverflowException) { throw new OverflowException("Число выходит за границы типа int."); }
    }

    // Задание 3
    class CreditCard
    {
        public string Number { get; }
        public string OwnerName { get; }
        public int CVC { get; }
        public DateTime ExpiryDate { get; }

        public CreditCard(string number, string ownerName, int cvc, DateTime expiryDate)
        {
            if (string.IsNullOrWhiteSpace(number) || number.Length != 16 || !long.TryParse(number, out _))
                throw new ArgumentException("Номер карты должен содержать 16 цифр");
            if (string.IsNullOrWhiteSpace(ownerName))
                throw new ArgumentException("ФИО владельца не может быть пустым");
            if (cvc < 100 || cvc > 999)
                throw new ArgumentException("CVC должен быть трёхзначным числом");
            if (expiryDate <= DateTime.Now)
                throw new ArgumentException("Дата завершения работы карты должна быть в будущем");

            Number = number;
            OwnerName = ownerName;
            CVC = cvc;
            ExpiryDate = expiryDate;
        }
    }

    // Задание 4
    static int EvaluateMultiplication(string input)
    {
        if (string.IsNullOrEmpty(input))
            throw new FormatException("Пустая строка");
        string[] parts = input.Split('*');
        int result = 1;
        foreach (string part in parts)
        {
            if (!int.TryParse(part, out int number))
                throw new FormatException($"Некорректное число: {part}");
            try { result = checked(result * number); }
            catch (OverflowException) { throw new OverflowException("Результат выходит за границы типа int"); }
        }
        return result;
    }
}