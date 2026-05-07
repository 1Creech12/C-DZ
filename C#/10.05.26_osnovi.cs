using System;

namespace TasksSolution
{
    class Program
    {
        static void Main(string[] args)
        {
            // Задание 1: Квадраты на прямоугольнике
            Console.WriteLine("Задание 1");
            Task1();

            Console.WriteLine("\nЗадание 2");
            Task2();

            Console.WriteLine("\nЗадание 3");
            Task3();

            Console.WriteLine("\nЗадание 4");
            Task4();

            Console.WriteLine("\nНажмите для выхода");
            Console.ReadKey();
        }

        static void Task1()
        {
            int A, B, C;

            A = GetPositiveInt("Введите A (длина прямоугольника): ");
            B = GetPositiveInt("Введите B (ширина прямоугольника): ");
            C = GetPositiveInt("Введите C (сторона квадрата): ");

            if (C > A || C > B)
            {
                Console.WriteLine("Невозможно разместить ни одного квадрата! Сторона квадрата превышает размеры прямоугольника.");
                return;
            }

            int countHorizontal = A / C;
            int countVertical = B / C;
            int totalSquares = countHorizontal * countVertical;

            int occupiedArea = totalSquares * (C * C);
            int totalArea = A * B;
            int freeArea = totalArea - occupiedArea;

            Console.WriteLine($"Размещено квадратов: {totalSquares}");
            Console.WriteLine($"Площадь незанятой части: {freeArea}");
        }

        static void Task2()
        {
            double P;
            Console.Write("Введите ежемесячный процент P (0 < P < 25): ");
            
            while (!double.TryParse(Console.ReadLine(), out P) || P <= 0 || P >= 25)
            {
                Console.Write("Некорректный ввод! Введите вещественное число от 0 до 25: ");
            }

            const double initialDeposit = 10000.0;
            const double targetDeposit = 11000.0;
            double currentDeposit = initialDeposit;
            int months = 0;

            while (currentDeposit <= targetDeposit)
            {
                currentDeposit += currentDeposit * (P / 100.0);
                months++;
            }

            Console.WriteLine($"Количество месяцев: {months}");
            Console.WriteLine($"Итоговый размер вклада: {currentDeposit:F2} руб.");
        }

        static void Task3()
        {
            int A, B;

            A = GetPositiveInt("Введите A (начало диапазона): ");
            B = GetPositiveInt("Введите B (конец диапазона, A < B): ");

            while (A >= B)
            {
                Console.WriteLine("Ошибка! A должно быть меньше B.");
                A = GetPositiveInt("Введите A (начало диапазона): ");
                B = GetPositiveInt("Введите B (конец диапазона, A < B): ");
            }

            Console.WriteLine("Результат:");
            for (int i = A; i <= B; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    if (j > 0) Console.Write(" ");
                    Console.Write(i);
                }
                Console.WriteLine();
            }
        }

        static void Task4()
        {
            int N = GetPositiveInt("Введите целое положительное число N: ");
            int reversed = 0;
            int original = N;

            while (N > 0)
            {
                int digit = N % 10;
                reversed = reversed * 10 + digit;
                N /= 10;
            }

            Console.WriteLine($"Исходное число: {original}");
            Console.WriteLine($"Число справа налево: {reversed}");
        }

        // Вспомогательный метод для ввода положительного целого числа
        static int GetPositiveInt(string message)
        {
            int number;
            Console.Write(message);
            
            while (!int.TryParse(Console.ReadLine(), out number) || number <= 0)
            {
                Console.Write("Некорректный ввод! Введите целое положительное число: ");
            }
            
            return number;
        }
    }
}