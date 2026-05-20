using System;

public abstract class Figure
{
    public abstract double FigureArea { get; }
    public abstract double FigurePerimeter { get; }
}

// Интерфейс
public interface IPolygonal
{
    double Height { get; }
    double Base { get; }
    double CBBAS { get; }
    int SideCount { get; }
    double[] SideLengths { get; }
    double Area { get; }
    double Perimeter { get; }
}

// Треугольник
public class Triangle : Figure, IPolygonal
{
    public double SideA { get; }
    public double SideB { get; }
    public double SideC { get; }
    public double Height { get; }
    public double Base { get; }
    public double CBBAS { get; }
    public int SideCount => 3;
    public double[] SideLengths => new[] { SideA, SideB, SideC };
    public override double FigureArea => Area;
    public override double FigurePerimeter => Perimeter;
    public double Area { get; }
    public double Perimeter { get; }

    public Triangle(double a, double b, double c)
    {
        if (a <= 0 || b <= 0 || c <= 0)
            throw new ArgumentException("Стороны должны быть положительными");
        if (a + b <= c || a + c <= b || b + c <= a)
            throw new ArgumentException("Нериальнй треугольник");

        SideA = a; SideB = b; SideC = c;
        Base = a;
        Perimeter = a + b + c;
        double p = Perimeter / 2;
        Area = Math.Sqrt(p * (p - a) * (p - b) * (p - c));
        Height = 2 * Area / Base;
        CBBAS = Math.Asin(Height / b) * 180 / Math.PI;
    }
}

// Квадрат
public class Square : Figure, IPolygonal
{
    public double Side { get; }
    public double Height => Side;
    public double Base => Side;
    public double CBBAS => 90;
    public int SideCount => 4;
    public double[] SideLengths => new[] { Side, Side, Side, Side };
    public override double FigureArea => Area;
    public override double FigurePerimeter => Perimeter;
    public double Area => Side * Side;
    public double Perimeter => 4 * Side;

    public Square(double side)
    {
        if (side <= 0) throw new ArgumentException("Сторона должна быть положительной");
        Side = side;
    }
}

// Прямоугольник
public class Rectangle : Figure, IPolygonal
{
    public double Width { get; }
    public double Length { get; }
    public double Height => Width;
    public double Base => Length;
    public double CBBAS => 90;
    public int SideCount => 4;
    public double[] SideLengths => new[] { Length, Width, Length, Width };
    public override double FigureArea => Area;
    public override double FigurePerimeter => Perimeter;
    public double Area => Length * Width;
    public double Perimeter => 2 * (Length + Width);

    public Rectangle(double length, double width)
    {
        if (length <= 0 || width <= 0)
            throw new ArgumentException("Длинна и ширина должны быть положителными");
        Length = length; Width = width;
    }
}

// Составная фигура
//public class CompositeFigure
//{
    
//}

class Program
{
    static void Main()
    {
        var triangle = new Triangle(3, 4, 5);
        var square = new Square(5);
        var rectangle = new Rectangle(4, 6);

        Console.WriteLine($"Площадь треугольника: {triangle.Area:F2}");
        Console.WriteLine($"Площаьдь квадрата: {square.Area:F2}");
        Console.WriteLine($"Площадь прямоугольника: {rectangle.Area:F2}");


    }
}