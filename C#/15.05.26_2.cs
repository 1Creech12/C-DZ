using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        DrawSquare(5, '*');

        Console.WriteLine(IsPalindrome(1221));
        Console.WriteLine(IsPalindrome(7854));

        int[] original = { 1, 2, 6, -1, 88, 7, 6 };
        int[] filter = { 6, 88, 7 };
        int[] filtered = FilterArray(original, filter);
        Console.WriteLine(string.Join(" ", filtered));

        Website site = new Website("Test", "https://test.com", "Тест", "192.168.1.1");
        site.PrintInfo();

        Journal journal = new Journal("Наука", 2000, "Научный журнал", "+79149288402", "nau@gmail.com");
        journal.PrintInfo();

        Shop shop = new Shop("Магазин", "ул. Ленина, 2", "Продуктовый", "+79142875023", "shop@gmail.com");
        shop.PrintInfo();
    }

    static void DrawSquare(int side, char symbol)
    {
        for (int i = 0; i < side; i++)
        {
            Console.WriteLine(new string(symbol, side));
        }
    }

    static bool IsPalindrome(int num)
    {
        string s = num.ToString();
        char[] arr = s.ToCharArray();
        Array.Reverse(arr);
        return s == new string(arr);
    }

    static int[] FilterArray(int[] original, int[] filter)
    {
        List<int> result = new List<int>();
        foreach (int x in original)
            if (Array.IndexOf(filter, x) == -1)
                result.Add(x);
        return result.ToArray();
    }

    class Website
    {
        public string Name, Url, Description, Ip;

        public Website(string name, string url, string desc, string ip)
        {
            Name = name; Url = url; Description = desc; Ip = ip;
        }

        public void PrintInfo() =>
            Console.WriteLine($"{Name}, {Url}, {Description}, {Ip}");
    }

    class Journal
    {
        public string Title, Description, Phone, Email;
        public int Year;

        public Journal(string title, int year, string desc, string phone, string email)
        {
            Title = title; Year = year; Description = desc; Phone = phone; Email = email;
        }

        public void PrintInfo() =>
            Console.WriteLine($"{Title}, {Year}, {Description}, {Phone}, {Email}");
    }

    class Shop
    {
        public string Name, Address, Description, Phone, Email;

        public Shop(string name, string address, string desc, string phone, string email)
        {
            Name = name; Address = address; Description = desc; Phone = phone; Email = email;
        }

        public void PrintInfo() =>
            Console.WriteLine($"{Name}, {Address}, {Description}, {Phone}, {Email}");
    }
}