using System;

class Program
{
    static void Main()
    {
        Console.WriteLine("Задание 1");
        int[] arr1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 2, 4, 6 };
        int even = 0, odd = 0;
        for (int i = 0; i < arr1.Length; i++)
        {
            if (arr1[i] % 2 == 0) even++;
            else odd++;
        }
        int uniqueCount = 0;
        for (int i = 0; i < arr1.Length; i++)
        {
            bool isUnique = true;
            for (int j = 0; j < arr1.Length; j++)
            {
                if (i != j && arr1[i] == arr1[j])
                {
                    isUnique = false;
                    break;
                }
            }
            if (isUnique) uniqueCount++;
        }
        Console.WriteLine("Чётные: " + even + ", Нечётные: " + odd + ", Уникальные: " + uniqueCount);

        Console.WriteLine("\nЗадание 2");
        int[] arr2 = { 1, 5, 3, 9, 2, 8, 4, 12, 6 };
        Console.Write("Введите число: ");
        int num = int.Parse(Console.ReadLine());
        int count = 0;
        for (int i = 0; i < arr2.Length; i++)
            if (arr2[i] < num) count++;
        Console.WriteLine("Меньше " + num + ": " + count);

        Console.WriteLine("\nЗадание 3");
        int[] arr3 = { 7, 6, 5, 3, 4, 7, 6, 5, 8, 7, 6, 5 };
        Console.WriteLine("Массив: 7 6 5 3 4 7 6 5 8 7 6 5");
        Console.Write("Введите три числа через пробел: ");
        string[] input = Console.ReadLine().Split(' ');
        int a = int.Parse(input[0]);
        int b = int.Parse(input[1]);
        int c = int.Parse(input[2]);
        int seqCount = 0;
        for (int i = 0; i < arr3.Length - 2; i++)
            if (arr3[i] == a && arr3[i + 1] == b && arr3[i + 2] == c)
                seqCount++;
        Console.WriteLine("Повторений: " + seqCount);

        Console.WriteLine("\nЗадание 4");
        int[] m = { 1, 2, 3, 4, 5 };
        int[] n = { 3, 4, 5, 6, 7 };
        int[] temp = new int[Math.Min(m.Length, n.Length)];
        int tempIndex = 0;
        for (int i = 0; i < m.Length; i++)
        {
            for (int j = 0; j < n.Length; j++)
            {
                if (m[i] == n[j])
                {
                    bool alreadyAdded = false;
                    for (int k = 0; k < tempIndex; k++)
                    {
                        if (temp[k] == m[i])
                        {
                            alreadyAdded = true;
                            break;
                        }
                    }
                    if (!alreadyAdded)
                    {
                        temp[tempIndex] = m[i];
                        tempIndex++;
                    }
                    break;
                }
            }
        }
        Console.Write("Общие элементы: ");
        for (int i = 0; i < tempIndex; i++)
            Console.Write(temp[i] + " ");
        Console.WriteLine();

        Console.WriteLine("\nЗадание 5");
        int[,] matrix = { { 3, 8, 1 }, { 12, 5, 9 }, { 2, 7, 4 } };
        int min = matrix[0, 0], max = matrix[0, 0];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (matrix[i, j] < min) min = matrix[i, j];
                if (matrix[i, j] > max) max = matrix[i, j];
            }
        }
        Console.WriteLine("Минимум: " + min + ", Максимум: " + max);

        Console.WriteLine("\nЗадание 6");
        Console.Write("Введите предложение: ");
        string str6 = Console.ReadLine();
        int words = 0;
        bool inWord = false;
        for (int i = 0; i < str6.Length; i++)
        {
            if (str6[i] != ' ')
            {
                if (!inWord)
                {
                    words++;
                    inWord = true;
                }
            }
            else
            {
                inWord = false;
            }
        }
        Console.WriteLine("Слов: " + words);

        Console.WriteLine("\nЗадание 7");
        Console.Write("Введите предложение: ");
        string str7 = Console.ReadLine();
        string result = "";
        string word = "";
        for (int i = 0; i < str7.Length; i++)
        {
            if (str7[i] != ' ')
            {
                word = str7[i] + word;
            }
            else
            {
                result += word + " ";
                word = "";
            }
        }
        result += word;
        Console.WriteLine("Результат: " + result);

        Console.WriteLine("\nЗадание 8");
        Console.Write("Введите предложение: ");
        string str8 = Console.ReadLine().ToLower();
        int vowels = 0;
        string vowelsList = "aeiouаеёиоуыэюя";
        for (int i = 0; i < str8.Length; i++)
        {
            for (int j = 0; j < vowelsList.Length; j++)
            {
                if (str8[i] == vowelsList[j])
                {
                    vowels++;
                    break;
                }
            }
        }
        Console.WriteLine("Гласных: " + vowels);

        Console.WriteLine("\nЗадание 9");
        Console.Write("Введите строку: ");
        string source = Console.ReadLine();
        Console.Write("Введите подстроку: ");
        string sub = Console.ReadLine();
        int occ = 0;
        for (int i = 0; i <= source.Length - sub.Length; i++)
        {
            bool match = true;
            for (int j = 0; j < sub.Length; j++)
            {
                if (source[i + j] != sub[j])
                {
                    match = false;
                    break;
                }
            }
            if (match) occ++;
        }
        Console.WriteLine("Вхождений: " + occ);
    }
}