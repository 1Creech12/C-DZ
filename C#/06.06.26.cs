using System;
using System.Globalization;
using System.IO;
using System.Xml;
using System.Xml.Serialization;

[Serializable]
public class RentalInvoice : IXmlSerializable
{
    public static bool IncludeComputedProperties { get; set; } = false;

    public decimal DailyCharge { get; set; }
    public int RentalDuration { get; set; }
    public decimal LateFeePerDay { get; set; }
    public int LateDays { get; set; }

    [XmlIgnore]
    public decimal BaseRentalCost => DailyCharge * RentalDuration;

    [XmlIgnore]
    public decimal LateFeeTotal => LateFeePerDay * LateDays;

    [XmlIgnore]
    public decimal GrandTotal => BaseRentalCost + LateFeeTotal;

    public override string ToString()
    {
        return $"Тариф/сутки: {DailyCharge}, Длительность аренды: {RentalDuration}\n" +
               $"Пеня/день просрочки: {LateFeePerDay}, Дней просрочки: {LateDays}\n" +
               $"Стоимость аренды: {BaseRentalCost}, Пеня: {LateFeeTotal}\n" +
               $"Общая сумма: {GrandTotal}\n";
    }

    public System.Xml.Schema.XmlSchema GetSchema() { return null; }

    public void WriteXml(XmlWriter writer)
    {
        var format = CultureInfo.InvariantCulture.NumberFormat;

        writer.WriteStartElement("PrimaryData");
        writer.WriteElementString("Tariff", DailyCharge.ToString(format));
        writer.WriteElementString("Period", RentalDuration.ToString());
        writer.WriteEndElement();

        writer.WriteStartElement("PenaltyInfo");
        writer.WriteElementString("FeePerDay", LateFeePerDay.ToString(format));
        writer.WriteElementString("OverduePeriod", LateDays.ToString());
        writer.WriteEndElement();

        if (IncludeComputedProperties)
        {
            writer.WriteStartElement("ComputedValues");
            writer.WriteElementString("Subtotal", BaseRentalCost.ToString(format));
            writer.WriteElementString("Penalty", LateFeeTotal.ToString(format));
            writer.WriteElementString("Total", GrandTotal.ToString(format));
            writer.WriteEndElement();
        }
    }

    public void ReadXml(XmlReader reader)
    {
        if (reader.IsEmptyElement)
        {
            reader.Read();
            return;
        }

        reader.ReadStartElement();

        reader.ReadStartElement("PrimaryData");
        DailyCharge = decimal.Parse(reader.ReadElementString("Tariff"), CultureInfo.InvariantCulture);
        RentalDuration = int.Parse(reader.ReadElementString("Period"));
        reader.ReadEndElement();

        reader.ReadStartElement("PenaltyInfo");
        LateFeePerDay = decimal.Parse(reader.ReadElementString("FeePerDay"), CultureInfo.InvariantCulture);
        LateDays = int.Parse(reader.ReadElementString("OverduePeriod"));
        reader.ReadEndElement();

        reader.ReadEndElement();
    }
}

class Program
{
    static void Main(string[] args)
    {
        var invoice = new RentalInvoice
        {
            DailyCharge = 250.75m,
            RentalDuration = 3,
            LateFeePerDay = 45.00m,
            LateDays = 1
        };

        RentalInvoice.IncludeComputedProperties = false;
        SerializeInvoice("invoice_simple.xml", invoice);

        RentalInvoice.IncludeComputedProperties = true;
        SerializeInvoice("invoice_detailed.xml", invoice);

        Console.WriteLine("Десериализация из 'invoice_simple.xml'");
        var loadedInvoice = DeserializeInvoice("invoice_simple.xml");
        Console.WriteLine(loadedInvoice);

        Console.WriteLine("Нажмите любую клавишу");
        Console.ReadKey();
    }

    static void SerializeInvoice(string filePath, RentalInvoice invoice)
    {
        var serializer = new XmlSerializer(typeof(RentalInvoice));
        using (var stream = new FileStream(filePath, FileMode.Create))
        {
            serializer.Serialize(stream, invoice);
        }
        Console.WriteLine($"Файл сохранён: {filePath}");
    }

    static RentalInvoice DeserializeInvoice(string filePath)
    {
        var serializer = new XmlSerializer(typeof(RentalInvoice));
        using (var stream = new FileStream(filePath, FileMode.Open))
        {
            return (RentalInvoice)serializer.Deserialize(stream);
        }
    }
}