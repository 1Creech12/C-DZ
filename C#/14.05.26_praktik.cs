using System;

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Задание 1");
        int[] array1 = { 0, 5, 0, 3, 0, 8, 0 };
        Console.WriteLine("Исходный массив: " + string.Join(", ", array1));
        int index1 = 0;

        for (int i = 0; i < array1.Length; i++)
        {
            if (array1[i] != 0)
            {
                array1[index1] = array1[i];
                index1++;
            }
        }

        for (int i = index1; i < array1.Length; i++)
        {
            array1[i] = -1;
        }

        Console.WriteLine(string.Join(", ", array1));

        Console.WriteLine("\nЗадание 2");
        int[] array2 = { 3, -2, 5, -8, 0, -1, 4 };
        Console.WriteLine("Исходный массив: " + string.Join(", ", array2));
        int[] result2 = new int[array2.Length];
        int index2 = 0;

        for (int i = 0; i < array2.Length; i++)
        {
            if (array2[i] < 0)
            {
                result2[index2] = array2[i];
                index2++;
            }
        }

        for (int i = 0; i < array2.Length; i++)
        {
            if (array2[i] >= 0)
            {
                result2[index2] = array2[i];
                index2++;
            }
        }

        Console.WriteLine(string.Join(", ", result2));

        Console.WriteLine("\nЗадание 3");
        int[] array3 = { 1, 5, 3, 5, 7, 5, 9 };
        Console.WriteLine("Исходный массив: " + string.Join(", ", array3));
        Console.Write("Введите число: ");
        int number = int.Parse(Console.ReadLine());
        int count = 0;

        for (int i = 0; i < array3.Length; i++)
        {
            if (array3[i] == number)
                count++;
        }

        Console.WriteLine($"Число {number} встречается {count} раз(а)");

        Console.WriteLine("\nЗадание 4");
        int[,] array4 = {
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 },
            { 9, 10, 11, 12 }
        };

        int rows = array4.GetLength(0);
        int cols = array4.GetLength(1);

        Console.WriteLine("Исходный массив:");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                Console.Write(array4[i, j] + " ");
            Console.WriteLine();
        }

        Console.Write("Номер первого столбца (от 0): ");
        int col1;
        string input1;
        while (true)
        {
            Console.Write("Номер первого столбца (от 0): ");
            input1 = Console.ReadLine();
            if (int.TryParse(input1, out col1) && col1 >= 0 && col1 < cols)
                break;
            Console.WriteLine("Ошибка. Введите целое число от 0 до " + (cols - 1));
        }

        Console.Write("Номер второго столбца (от 0): ");
        int col2;
        string input2;
        while (true)
        {
            Console.Write("Номер второго столбца (от 0): ");
            input2 = Console.ReadLine();
            if (int.TryParse(input2, out col2) && col2 >= 0 && col2 < cols)
                break;
            Console.WriteLine("Ошибка. Введите целое число от 0 до " + (cols - 1));
        }

        
        for (int i = 0; i < rows; i++)
        {
            int temp = array4[i, col1];
            array4[i, col1] = array4[i, col2];
            array4[i, col2] = temp;
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                Console.Write(array4[i, j] + " ");
            Console.WriteLine();
        
        }
    }
}