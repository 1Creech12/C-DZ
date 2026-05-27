using System;
using System.Collections.Generic;

public abstract class Figure
{
    public abstract double FigureArea { get; }
    public abstract double FigurePerimeter { get; }
}

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
            throw new ArgumentException("Нереальный треугольник");

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
            throw new ArgumentException("Длина и ширина должны быть положительными");
        Length = length; Width = width;
    }
}

// Ромб
public class Rhombus : Figure, IPolygonal
{
    public double Side { get; }
    public double Diagonal1 { get; }
    public double Diagonal2 { get; }
    public double Height { get; }
    public double Base => Side;
    public double CBBAS { get; }
    public int SideCount => 4;
    public double[] SideLengths => new[] { Side, Side, Side, Side };
    public override double FigureArea => Area;
    public override double FigurePerimeter => Perimeter;
    public double Area => (Diagonal1 * Diagonal2) / 2;
    public double Perimeter => 4 * Side;

    public Rhombus(double side, double d1, double d2)
    {
        if (side <= 0 || d1 <= 0 || d2 <= 0)
            throw new ArgumentException("Параметры должны быть положительными");
        Side = side;
        Diagonal1 = d1;
        Diagonal2 = d2;
        Height = Area / Side;
        CBBAS = Math.Asin(Height / Side) * 180 / Math.PI;
    }
}

// Параллелограмм
public class Parallelogram : Figure, IPolygonal
{
    public double SideA { get; }
    public double SideB { get; }
    public double Height { get; }
    public double Base => SideA;
    public double CBBAS { get; }
    public int SideCount => 4;
    public double[] SideLengths => new[] { SideA, SideB, SideA, SideB };
    public override double FigureArea => Area;
    public override double FigurePerimeter => Perimeter;
    public double Area => SideA * Height;
    public double Perimeter => 2 * (SideA + SideB);

    public Parallelogram(double sideA, double sideB, double height)
    {
        if (sideA <= 0 || sideB <= 0 || height <= 0)
            throw new ArgumentException("Параметры должны быть положительными");
        if (height > sideB)
            throw new ArgumentException("Высота не может быть больше боковой стороны");
        SideA = sideA;
        SideB = sideB;
        Height = height;
        CBBAS = Math.Asin(Height / SideB) * 180 / Math.PI;
    }
}

// Трапеция
public class Trapezoid : Figure, IPolygonal
{
    public double BaseA { get; }
    public double BaseB { get; }
    public double SideC { get; }
    public double SideD { get; }
    public double Height { get; }
    public double Base => BaseA;
    public double CBBAS { get; }
    public int SideCount => 4;
    public double[] SideLengths => new[] { BaseA, SideC, BaseB, SideD };
    public override double FigureArea => Area;
    public override double FigurePerimeter => Perimeter;
    public double Area => (BaseA + BaseB) * Height / 2;
    public double Perimeter => BaseA + BaseB + SideC + SideD;

    public Trapezoid(double baseA, double baseB, double sideC, double sideD, double height)
    {
        if (baseA <= 0 || baseB <= 0 || sideC <= 0 || sideD <= 0 || height <= 0)
            throw new ArgumentException("Параметры должны быть положительными");
        BaseA = baseA;
        BaseB = baseB;
        SideC = sideC;
        SideD = sideD;
        Height = height;
        CBBAS = Math.Asin(Height / SideC) * 180 / Math.PI;
    }
}

// Круг
public class Circle : Figure
{
    public double Radius { get; }
    public override double FigureArea => Math.PI * Radius * Radius;
    public override double FigurePerimeter => 2 * Math.PI * Radius;

    public Circle(double radius)
    {
        if (radius <= 0)
            throw new ArgumentException("Радиус должен быть положительным");
        Radius = radius;
    }
}

// Эллипс
public class Ellipse : Figure
{
    public double SemiAxisA { get; }
    public double SemiAxisB { get; }
    public override double FigureArea => Math.PI * SemiAxisA * SemiAxisB;
    public override double FigurePerimeter
    {
        get
        {
            double diff = SemiAxisA - SemiAxisB;
            double sum = SemiAxisA + SemiAxisB;
            double h = (diff * diff) / (sum * sum);
            return Math.PI * sum * (1 + (3 * h) / (10 + Math.Sqrt(4 - 3 * h)));
        }
    }

    public Ellipse(double a, double b)
    {
        if (a <= 0 || b <= 0)
            throw new ArgumentException("Полуоси должны быть положительными");
        SemiAxisA = a;
        SemiAxisB = b;
    }
}

// Составная фигура
public class CompositeFigure : Figure
{
    private List<Figure> figures = new List<Figure>();
    
    public override double FigureArea
    {
        get
        {
            double total = 0;
            foreach (var f in figures)
                total += f.FigureArea;
            return total;
        }
    }
    
    public override double FigurePerimeter => 0;

    public void AddFigure(Figure figure)
    {
        figures.Add(figure);
    }

    public void RemoveFigure(Figure figure)
    {
        figures.Remove(figure);
    }

    public int FigureCount => figures.Count;
}

class Program
{
    static void Main()
    {
        var triangle = new Triangle(3, 4, 5);
        var square = new Square(5);
        var rectangle = new Rectangle(4, 6);
        var rhombus = new Rhombus(5, 6, 8);
        var parallelogram = new Parallelogram(5, 4, 3);
        var trapezoid = new Trapezoid(4, 8, 3, 3, 4);
        var circle = new Circle(5);
        var ellipse = new Ellipse(4, 2);

        Figure[] figures = { triangle, square, rectangle, rhombus, parallelogram, trapezoid, circle, ellipse };

        Console.WriteLine("Все фигуры\n");
        foreach (var fig in figures)
        {
            Console.WriteLine($"{fig.GetType().Name}:");
            Console.WriteLine($"  Площадь: {fig.FigureArea:F2}");
            Console.WriteLine($"  Периметр: {fig.FigurePerimeter:F2}");
            Console.WriteLine();
        }

        Console.WriteLine("Составная фигура\n");
        var composite = new CompositeFigure();
        composite.AddFigure(new Circle(3));
        composite.AddFigure(new Rectangle(4, 5));
        composite.AddFigure(new Triangle(3, 4, 5));
        
        Console.WriteLine($"Количество фигур в составе: {composite.FigureCount}");
        Console.WriteLine($"Общая площадь: {composite.FigureArea:F2}");

        Console.WriteLine("\nПроверка интерфейса IPolygonal\n");
        IPolygonal[] polygons = { triangle, square, rectangle, rhombus, parallelogram, trapezoid };
        foreach (var poly in polygons)
        {
            Console.WriteLine($"{poly.GetType().Name}: сторон {poly.SideCount}, площадь {poly.Area:F2}");
        }
    }
}