using System;
using System.Collections.Generic;
using System.Linq;

// Задание 1
struct Article
{
    public int ProductCode;
    public string ProductName;
    public decimal Price;
}

// Задание 2
struct Client
{
    public int ClientCode;
    public string FullName;
    public string Address;
    public string Phone;
    public int OrderCount;
    public decimal TotalOrderAmount;
}

// Задание 3
struct RequestItem
{
    public Article Product;
    public int Quantity;
}

// Задание 4
struct Request
{
    public int OrderCode;
    public Client Client;
    public DateTime OrderDate;
    public List<RequestItem> Items;
    
    public decimal TotalAmount
    {
        get
        {
            if (Items == null || Items.Count == 0)
                return 0;
            return Items.Sum(item => item.Product.Price * item.Quantity);
        }
    }
}

class Program
{
    static void Main()
    {
        Article book = new Article { ProductCode = 1, ProductName = "Книга", Price = 500m };
        Article pen = new Article { ProductCode = 2, ProductName = "Ручка", Price = 50m };

        Client client = new Client
        {
            ClientCode = 100,
            FullName = "Иванов Андреевич Васькин",
            Address = "ул. Пушкина, д. 10",
            Phone = "+7924832884",
            OrderCount = 5,
            TotalOrderAmount = 15000m
        };
        
        RequestItem item1 = new RequestItem { Product = book, Quantity = 2 };
        RequestItem item2 = new RequestItem { Product = pen, Quantity = 5 };

        Request order = new Request
        {
            OrderCode = 1001,
            Client = client,
            OrderDate = DateTime.Now,
            Items = new List<RequestItem> { item1, item2 }
        };

        Console.WriteLine($"Заказ №{order.OrderCode}");
        Console.WriteLine($"Клиент: {order.Client.FullName}");
        Console.WriteLine($"Дата: {order.OrderDate}");
        Console.WriteLine($"Сумма заказа: {order.TotalAmount} руб.");
    }
}