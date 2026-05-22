using System;

enum ArticleType { Food, Electronics, Clothing, Books }

struct Article
{
    public int Code;
    public string Name;
    public double Price;
    public ArticleType Type;

    public Article(int code, string name, double price, ArticleType type)
    {
        Code = code; Name = name; Price = price; Type = type;
    }
}

enum ClientType { Regular, VIP, Wholesale }

struct Client
{
    public int Code;
    public string FullName;
    public string Address;
    public string Phone;
    public int OrderCount;
    public double TotalAmount;
    public ClientType Type;

    public Client(int code, string name, string address, string phone, ClientType type)
    {
        Code = code; FullName = name; Address = address; Phone = phone;
        OrderCount = 0; TotalAmount = 0; Type = type;
    }
}

struct RequestItem
{
    public Article Product;
    public int Quantity;

    public RequestItem(Article product, int quantity)
    {
        Product = product; Quantity = quantity;
    }
}

enum PayType { Cash, Card, Online }

struct Request
{
    public int Code;
    public Client Customer;
    public DateTime Date;
    public RequestItem[] Items;
    public PayType Payment;

    public double Sum
    {
        get
        {
            if (Items == null) return 0;
            double total = 0;
            foreach (var item in Items)
                total += item.Product.Price * item.Quantity;
            return total;
        }
    }
}

class Student
{
    public string LastName;
    public string FirstName;
    public string MiddleName;
    public string Group;
    public int Age;
    public int[][] Grades;

    public Student(string lastName, string firstName, string middleName, string group, int age)
    {
        LastName = lastName;
        FirstName = firstName;
        MiddleName = middleName;
        Group = group;
        Age = age;
        Grades = new int[3][];
        Grades[0] = new int[0];
        Grades[1] = new int[0];
        Grades[2] = new int[0];
    }

    public void SetGrade(int subject, int grade)
    {
        Array.Resize(ref Grades[subject], Grades[subject].Length + 1);
        Grades[subject][Grades[subject].Length - 1] = grade;
    }

    public double GetAverage(int subject)
    {
        if (Grades[subject].Length == 0) return 0;
        double sum = 0;
        foreach (int g in Grades[subject]) sum += g;
        return sum / Grades[subject].Length;
    }

    public void PrintInfo()
    {
        Console.WriteLine($"{LastName} {FirstName} {MiddleName}, группа {Group}, возраст {Age}");
        Console.WriteLine($"Средний балл программирование: {GetAverage(0):F2}");
        Console.WriteLine($"Средний балл администрирование: {GetAverage(1):F2}");
        Console.WriteLine($"Средний балл дизайн: {GetAverage(2):F2}");
    }
}

namespace SevenWonders
{
    class Pyramid { public void Show() => Console.WriteLine("Пирамида Хеопса"); }
    class HangingGardens { public void Show() => Console.WriteLine("Висячие сады Семирамиды"); }
    class ZeusStatue { public void Show() => Console.WriteLine("Статуя Зевса в Олимпии"); }
    class ArtemisTemple { public void Show() => Console.WriteLine("Храм Артемиды в Эфесе"); }
    class Mausoleum { public void Show() => Console.WriteLine("Мавзолей в Галикарнасе"); }
    class Colossus { public void Show() => Console.WriteLine("Колосс Родосский"); }
    class Lighthouse { public void Show() => Console.WriteLine("Александрийский маяк"); }
}

namespace Russia
{
    class Moscow
    {
        public double Population = 12.6;
        public void Show() => Console.WriteLine($"Москва: {Population} млн");
    }
}

namespace France
{
    class Paris
    {
        public double Population = 2.1;
        public void Show() => Console.WriteLine($"Париж: {Population} млн");
    }
}

namespace Japan
{
    class Tokyo
    {
        public double Population = 13.9;
        public void Show() => Console.WriteLine($"Токио: {Population} млн");
    }
}

class Program
{
    static void Main()
    {
        Console.WriteLine("7 чудес света:");
        var wonders = new object[]
        {
            new SevenWonders.Pyramid(),
            new SevenWonders.HangingGardens(),
            new SevenWonders.ZeusStatue(),
            new SevenWonders.ArtemisTemple(),
            new SevenWonders.Mausoleum(),
            new SevenWonders.Colossus(),
            new SevenWonders.Lighthouse()
        };
        foreach (dynamic wonder in wonders) wonder.Show();

        Console.WriteLine("\nНаселение столиц:");
        new Russia.Moscow().Show();
        new France.Paris().Show();
        new Japan.Tokyo().Show();

        Console.WriteLine("\nСтудент:");
        Student student = new Student("Иванов", "Абдул", "Арабович", "П-42", 20);
        student.SetGrade(0, 5);
        student.SetGrade(0, 4);
        student.SetGrade(1, 3);
        student.PrintInfo();
    }
}