using System;

class Program
{
    static void Main()
    {
        while (true)
        {
            Console.WriteLine("\nВыберите задание (1-7) или 0 для выхода:");
            string choice = Console.ReadLine();

            switch (choice)
            {
                case "1": 
                    Task1(); 
                    break;
                case "2": 
                    Task2(); 
                    break;
                case "3": 
                    Task3(); 
                    break;
                case "4": 
                    Task4(); 
                    break;
                case "5": 
                    Task5(); 
                    break;
                case "6": 
                    Task6(); 
                    break;
                case "7":
                    Task7(); 
                    break;
                case "0":
                    return;
                default: Console.WriteLine("Неверный выбор"); break;
            }
        }
    }

    static void Task1()
    {
        Console.Write("Введите число от 1 до 100: ");
        int number = int.Parse(Console.ReadLine());

        if (number < 1 || number > 100)
        {
            Console.WriteLine("Ошибка: число должно быть в диапазоне от 1 до 100");
        }
        else if (number % 3 == 0 && number % 5 == 0)
        {
            Console.WriteLine("Fizz Buzz");
        }
        else if (number % 3 == 0)
        {
            Console.WriteLine("Fizz");
        }
        else if (number % 5 == 0)
        {
            Console.WriteLine("Buzz");
        }
        else
        {
            Console.WriteLine(number);
        }
    }

    static void Task2()
    {
        Console.Write("Введите число: ");
        double value = double.Parse(Console.ReadLine());

        Console.Write("Введите процент: ");
        double percent = double.Parse(Console.ReadLine());

        double result = value * percent / 100;
        Console.WriteLine($"Результат: {result}");
    }

    static void Task3()
    {
        Console.Write("Введите первую цифру: ");
        int d1 = int.Parse(Console.ReadLine());

        Console.Write("Введите вторую цифру: ");
        int d2 = int.Parse(Console.ReadLine());

        Console.Write("Введите третью цифру: ");
        int d3 = int.Parse(Console.ReadLine());

        Console.Write("Введите четвертую цифру: ");
        int d4 = int.Parse(Console.ReadLine());

        int formedNumber = d1 * 1000 + d2 * 100 + d3 * 10 + d4;
        Console.WriteLine($"Сформированное число: {formedNumber}");
    }

    static void Task4()
    {
        Console.Write("Введите шестизначное число: ");
        string input = Console.ReadLine();

        if (input.Length != 6 || !long.TryParse(input, out _))
        {
            Console.WriteLine("Ошибка: введено не шестизначное число");
            return;
        }

        Console.Write("Введите первый номер разряда (1-6): ");
        int pos1 = int.Parse(Console.ReadLine()) - 1;

        Console.Write("Введите второй номер разряда (1-6): ");
        int pos2 = int.Parse(Console.ReadLine()) - 1;

        if (pos1 < 0 || pos1 > 5 || pos2 < 0 || pos2 > 5)
        {
            Console.WriteLine("Ошибка: номера разрядов должны быть от 1 до 6");
            return;
        }

        char[] digits = input.ToCharArray();
        char temp = digits[pos1];
        digits[pos1] = digits[pos2];
        digits[pos2] = temp;

        Console.WriteLine($"Результат: {new string(digits)}");
    }

    static void Task5()
    {
        Console.Write("Введите дату в формате д.м.г: ");
        DateTime date = DateTime.Parse(Console.ReadLine());

        string dayOfWeek = date.DayOfWeek.ToString();
        string season;
        int month = date.Month;

        if (month == 12 || month == 1 || month == 2)
            season = "Winter";
        else if (month >= 3 && month <= 5)
            season = "Spring";
        else if (month >= 6 && month <= 8)
            season = "Summer";
        else
            season = "Autumn";

        Console.WriteLine($"{season} {dayOfWeek}");
    }

    static void Task6()
    {
        Console.Write("Выберите направление:\n1 - Цельсий в Фаренгейт\n2 - Фаренгейт в Цельсий: ");
        int choice = int.Parse(Console.ReadLine());

        Console.Write("Введите температуру: ");
        double temp = double.Parse(Console.ReadLine());

        if (choice == 1)
            Console.WriteLine($"{temp}°C = {temp * 9 / 5 + 32}°F");
        else if (choice == 2)
            Console.WriteLine($"{temp}°F = {(temp - 32) * 5 / 9}°C");
        else
            Console.WriteLine("Неверный выбор");
    }

    static void Task7()
    {
        Console.Write("Введите первое число: ");
        int a = int.Parse(Console.ReadLine());

        Console.Write("Введите второе число: ");
        int b = int.Parse(Console.ReadLine());

        int start = Math.Min(a, b);
        int end = Math.Max(a, b);

        Console.WriteLine($"Четные числа от {start} до {end}:");
        for (int i = start; i <= end; i++)
        {
            if (i % 2 == 0)
                Console.Write(i + " ");
        }
        Console.WriteLine();
    }
}