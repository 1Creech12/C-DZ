using System;

// Задание 1
class Human
{
    public string Name { get; set; }
    public int Age { get; set; }

    public Human(string name, int age)
    {
        Name = name;
        Age = age;
    }

    public virtual void ShowInfo()
    {
        Console.WriteLine($"Имя: {Name}, Возраст: {Age}");
    }
}

class Builder : Human
{
    public string Speciality { get; set; }

    public Builder(string name, int age, string speciality) : base(name, age)
    {
        Speciality = speciality;
    }

    public void Build()
    {
        Console.WriteLine($"{Name} строит здание");
    }

    public override void ShowInfo()
    {
        base.ShowInfo();
        Console.WriteLine($"Специальность строителя: {Speciality}");
    }
}

class Sailor : Human
{
    public string ShipName { get; set; }

    public Sailor(string name, int age, string shipName) : base(name, age)
    {
        ShipName = shipName;
    }

    public void Sail()
    {
        Console.WriteLine($"{Name} плывет на корабле {ShipName}");
    }

    public override void ShowInfo()
    {
        base.ShowInfo();
        Console.WriteLine($"Корабль: {ShipName}");
    }
}

class Pilot : Human
{
    public string PlaneModel { get; set; }

    public Pilot(string name, int age, string planeModel) : base(name, age)
    {
        PlaneModel = planeModel;
    }

    public void Fly()
    {
        Console.WriteLine($"{Name} летит на самолете {PlaneModel}");
    }

    public override void ShowInfo()
    {
        base.ShowInfo();
        Console.WriteLine($"Самолет: {PlaneModel}");
    }
}

// Задание 2
class Passport
{
    public string CitizenName { get; set; }
    public string Country { get; set; }
    public string PassportNumber { get; set; }

    public Passport(string name, string country, string number)
    {
        CitizenName = name;
        Country = country;
        PassportNumber = number;
    }

    public virtual void ShowInfo()
    {
        Console.WriteLine($"Гражданин: {CitizenName}");
        Console.WriteLine($"Страна: {Country}");
        Console.WriteLine($"Номер паспорта: {PassportNumber}");
    }
}

class ForeignPassport : Passport
{
    public string ForeignPassportNumber { get; set; }
    public string[] Visas { get; set; }

    public ForeignPassport(string name, string country, string number, string foreignNumber, string[] visas) 
        : base(name, country, number)
    {
        ForeignPassportNumber = foreignNumber;
        Visas = visas;
    }

    public override void ShowInfo()
    {
        base.ShowInfo();
        Console.WriteLine($"Номер загранпаспорта: {ForeignPassportNumber}");
        Console.Write("Визы: ");
        if (Visas != null && Visas.Length > 0)
        {
            Console.WriteLine(string.Join(", ", Visas));
        }
        else
        {
            Console.WriteLine("нет виз");
        }
    }
}

// Задание 3
class Animal
{
    public string Name { get; set; }
    public string Habitat { get; set; }
    public double Weight { get; set; }

    public Animal(string name, string habitat, double weight)
    {
        Name = name;
        Habitat = habitat;
        Weight = weight;
    }

    public virtual void ShowInfo()
    {
        Console.WriteLine($"Животное: {Name}");
        Console.WriteLine($"Среда обитания: {Habitat}");
        Console.WriteLine($"Вес: {Weight} кг");
    }

    public virtual void MakeSound()
    {
        Console.WriteLine("Животное издает звук");
    }
}

class Tiger : Animal
{
    public int StripeCount { get; set; }

    public Tiger(string name, double weight, int stripeCount) 
        : base(name, "Джунгли", weight)
    {
        StripeCount = stripeCount;
    }

    public override void MakeSound()
    {
        Console.WriteLine($"{Name} рычит: Р-р-р-р!");
    }

    public override void ShowInfo()
    {
        base.ShowInfo();
        Console.WriteLine($"Количество полос: {StripeCount}");
    }
}

class Crocodile : Animal
{
    public double JawStrength { get; set; }

    public Crocodile(string name, double weight, double jawStrength) 
        : base(name, "Реки и болота", weight)
    {
        JawStrength = jawStrength;
    }

    public override void MakeSound()
    {
        Console.WriteLine($"{Name} щелкает челюстями!");
    }

    public override void ShowInfo()
    {
        base.ShowInfo();
        Console.WriteLine($"Сила челюстей: {JawStrength} Н");
    }
}

class Kangaroo : Animal
{
    public double JumpHeight { get; set; }

    public Kangaroo(string name, double weight, double jumpHeight) 
        : base(name, "Австралия", weight)
    {
        JumpHeight = jumpHeight;
    }

    public override void MakeSound()
    {
        Console.WriteLine($"{Name} цокает!");
    }

    public override void ShowInfo()
    {
        base.ShowInfo();
        Console.WriteLine($"Высота прыжка: {JumpHeight} м");
    }
}

// Задание 4
abstract class Figure
{
    public abstract double GetArea();
}

class Rectangle : Figure
{
    public double Width { get; set; }
    public double Height { get; set; }

    public Rectangle(double width, double height)
    {
        Width = width;
        Height = height;
    }

    public override double GetArea()
    {
        return Width * Height;
    }
}

class Circle : Figure
{
    public double Radius { get; set; }

    public Circle(double radius)
    {
        Radius = radius;
    }

    public override double GetArea()
    {
        return Math.PI * Radius * Radius;
    }
}

class RightTriangle : Figure
{
    public double Leg1 { get; set; }
    public double Leg2 { get; set; }

    public RightTriangle(double leg1, double leg2)
    {
        Leg1 = leg1;
        Leg2 = leg2;
    }

    public override double GetArea()
    {
        return 0.5 * Leg1 * Leg2;
    }
}

class Trapezoid : Figure
{
    public double Base1 { get; set; }
    public double Base2 { get; set; }
    public double Height { get; set; }

    public Trapezoid(double base1, double base2, double height)
    {
        Base1 = base1;
        Base2 = base2;
        Height = height;
    }

    public override double GetArea()
    {
        return 0.5 * (Base1 + Base2) * Height;
    }
}

class Program
{
    static void Main()
    {
        Console.WriteLine("Задание 1");
        Human builder = new Builder("Иван", 35, "каменщик");
        Human sailor = new Sailor("Петр", 28, "Аврора");
        Human pilot = new Pilot("Анна", 32, "Boeing 747");
        
        builder.ShowInfo();
        ((Builder)builder).Build();
        Console.WriteLine();
        
        sailor.ShowInfo();
        ((Sailor)sailor).Sail();
        Console.WriteLine();
        
        pilot.ShowInfo();
        ((Pilot)pilot).Fly();
        
        Console.WriteLine("\nЗадание 2");
        string[] visas = { "США", "Китай", "Япония" };
        ForeignPassport fp = new ForeignPassport("Алексей", "Россия", "4512-123456", "75-98765432", visas);
        fp.ShowInfo();
        
        Console.WriteLine("\nЗадание 3");
        Animal[] animals = new Animal[3];
        animals[0] = new Tiger("Шерхан", 250, 80);
        animals[1] = new Crocodile("Гена", 500, 5000);
        animals[2] = new Kangaroo("Кенгу", 80, 3.5);
        
        foreach (Animal animal in animals)
        {
            animal.ShowInfo();
            animal.MakeSound();
            Console.WriteLine();
        }
        
        Console.WriteLine("Задание 4");
        Figure[] figures = new Figure[4];
        figures[0] = new Rectangle(5, 10);
        figures[1] = new Circle(7);
        figures[2] = new RightTriangle(3, 4);
        figures[3] = new Trapezoid(4, 8, 5);
        
        foreach (Figure figure in figures)
        {
            Console.WriteLine($"Площадь {figure.GetType().Name}: {figure.GetArea():F2}");
        }
    }
}