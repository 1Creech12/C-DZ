using System;

class Program
{
    static void Main()
    {
        // Задание 1
        DrawSquare(5, '*');
        
        // Задание 2
        Console.WriteLine(IsPalindrome(1221));
        Console.WriteLine(IsPalindrome(7854));
        
        // Задание 3
        int[] original = { 1, 2, 6, -1, 88, 7, 6 };
        int[] filter = { 6, 88, 7 };
        int[] result = FilterArray(original, filter);
        Console.WriteLine(string.Join(" ", result));
    }
    
    static void DrawSquare(int length, char symbol)
    {
        for (int i = 0; i < length; i++)
        {
            Console.WriteLine(new string(symbol, length));
        }
    }
    
    static bool IsPalindrome(int number)
    {
        string s = number.ToString();
        for (int i = 0; i < s.Length / 2; i++)
        {
            if (s[i] != s[s.Length - 1 - i])
                return false;
        }
        return true;
    }
    
    static int[] FilterArray(int[] original, int[] filter)
    {
        int count = 0;
        for (int i = 0; i < original.Length; i++)
        {
            bool remove = false;
            for (int j = 0; j < filter.Length; j++)
            {
                if (original[i] == filter[j])
                {
                    remove = true;
                    break;
                }
            }
            if (!remove) count++;
        }
        
        int[] result = new int[count];
        int index = 0;
        for (int i = 0; i < original.Length; i++)
        {
            bool remove = false;
            for (int j = 0; j < filter.Length; j++)
            {
                if (original[i] == filter[j])
                {
                    remove = true;
                    break;
                }
            }
            if (!remove)
            {
                result[index] = original[i];
                index++;
            }
        }
        return result;
    }
}