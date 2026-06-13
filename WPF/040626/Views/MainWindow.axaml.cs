using Avalonia.Controls;
using Avalonia.Interactivity;
using System;
using System.IO;
using System.Xml;

namespace _040626.Views
{
    public partial class MainWindow : Window
    {
        private readonly string _filePath = Path.Combine(
            Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), 
            "Orders.xml");
        private TextBox OutText => this.FindControl<TextBox>("OutputTextBox")!;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void OnCreateXmlClick(object? sender, RoutedEventArgs e)
        {
            try
            {
                using (XmlTextWriter writer = new XmlTextWriter(_filePath, System.Text.Encoding.UTF8))
                {
                    writer.Formatting = Formatting.Indented;
                    writer.WriteStartDocument();
                    writer.WriteStartElement("Orders");

                    writer.WriteStartElement("Order");
                    writer.WriteAttributeString("Id", "1");
                    writer.WriteAttributeString("Date", DateTime.Now.ToString("yyyy-MM-dd"));
                    writer.WriteAttributeString("Customer", "Васька Пупкин");
                    
                    writer.WriteStartElement("Items");
                    writer.WriteStartElement("Item");
                    writer.WriteAttributeString("Name", "Ноутбук");
                    writer.WriteAttributeString("Price", "1500");
                    writer.WriteAttributeString("Quantity", "1");
                    writer.WriteEndElement(); 

                    writer.WriteStartElement("Item");
                    writer.WriteAttributeString("Name", "Мышь");
                    writer.WriteAttributeString("Price", "50");
                    writer.WriteAttributeString("Quantity", "2");
                    writer.WriteEndElement(); 

                    writer.WriteEndElement();
                    writer.WriteEndElement();

                    writer.WriteStartElement("Order");
                    writer.WriteAttributeString("Id", "2");
                    writer.WriteAttributeString("Date", DateTime.Now.ToString("yyyy-MM-dd"));
                    writer.WriteAttributeString("Customer", "Васька Пупкин");
                    
                    writer.WriteStartElement("Items");
                    writer.WriteStartElement("Item");
                    writer.WriteAttributeString("Name", "Клавиатура");
                    writer.WriteAttributeString("Price", "120");
                    writer.WriteAttributeString("Quantity", "1");
                    writer.WriteEndElement(); 

                    writer.WriteEndElement();
                    writer.WriteEndElement();

                    writer.WriteEndElement();
                    writer.WriteEndDocument();
                }
                
                OutText.Text = $"Файл создан\nПуть: {_filePath}";
            }
            catch (Exception ex)
            {
                OutText.Text = $"Ошибка при создании: {ex.Message}";
            }
        }

        private void OnReadXmlDocumentClick(object? sender, RoutedEventArgs e)
        {
            if (!File.Exists(_filePath))
            {
                OutText.Text = "Файл не найден";
                return;
            }

            try
            {
                XmlDocument doc = new XmlDocument();
                doc.Load(_filePath);
                
                string output = "Чтение через XmlDocument\n\n";
                XmlNodeList? orders = doc.GetElementsByTagName("Order");
                
                if (orders != null)
                {
                    foreach (XmlNode order in orders)
                    {
                        string id = order.Attributes?["Id"]?.Value ?? "N/A";
                        string cust = order.Attributes?["Customer"]?.Value ?? "N/A";
                        output += $"Заказ #{id} (Клиент: {cust})\n";
                        
                        XmlNode? itemsNode = order.SelectSingleNode("Items");
                        if (itemsNode != null && itemsNode.HasChildNodes)
                        {
                            foreach (XmlNode item in itemsNode.ChildNodes)
                            {
                                if (item.NodeType == XmlNodeType.Element)
                                {
                                    string name = item.Attributes?["Name"]?.Value ?? "";
                                    string price = item.Attributes?["Price"]?.Value ?? "";
                                    string qty = item.Attributes?["Quantity"]?.Value ?? "";
                                    output += $"   • {name} | Цена: {price}$ | Кол-во: {qty}\n";
                                }
                            }
                        }
                        output += "\n";
                    }
                }
                OutText.Text = output;
            }
            catch (Exception ex)
            {
                OutText.Text = $"Ошибка чтения (XmlDocument): {ex.Message}";
            }
        }

        private void OnReadXmlTextReaderClick(object? sender, RoutedEventArgs e)
        {
            if (!File.Exists(_filePath))
            {
                OutText.Text = "Файл не найден";
                return;
            }

            try
            {
                string output = "Чтение через XmlTextReader";
                
                using (XmlTextReader reader = new XmlTextReader(_filePath))
                {
                    reader.WhitespaceHandling = WhitespaceHandling.None;
                    
                    while (reader.Read())
                    {
                        if (reader.NodeType == XmlNodeType.Element)
                        {
                            if (reader.Name == "Order")
                            {
                                string id = reader.GetAttribute("Id") ?? "";
                                string cust = reader.GetAttribute("Customer") ?? "";
                                output += $"Заказ #{id} (Клиент: {cust})\n";
                            }
                            else if (reader.Name == "Item")
                            {
                                string name = reader.GetAttribute("Name") ?? "";
                                string price = reader.GetAttribute("Price") ?? "";
                                string qty = reader.GetAttribute("Quantity") ?? "";
                                output += $"   • {name} | Цена: {price}$ | Кол-во: {qty}\n";
                            }
                        }
                    }
                }
                OutText.Text = output;
            }
            catch (Exception ex)
            {
                OutText.Text = $"Ошибка чтения (XmlTextReader): {ex.Message}";
            }
        }
    }
}