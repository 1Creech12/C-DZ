using System;
using System.Collections.Generic;

namespace FinancialUtilities
{
    public class NegativeValueException : Exception
    {
        public NegativeValueException(string message) : base(message) { }
        public NegativeValueException(string message, Exception inner) : base(message, inner) { }
    }

    public class OverdraftException : Exception
    {
        public OverdraftException(string message) : base(message) { }
        public OverdraftException(string message, Exception inner) : base(message, inner) { }
    }

    public class ClientWallet
    {
        private static int _walletCounter = 5000;

        public string WalletId { get; private set; }
        public double CashAmount { get; private set; }

        public ClientWallet(double startingCash = 0)
        {
            if (startingCash < 0)
                throw new NegativeValueException("Стартовый капитал не может быть меньше нуля");

            WalletId = $"WLT-{_walletCounter++}";
            CashAmount = startingCash;
        }

        public void AddFunds(double sum)
        {
            if (sum <= 0)
                throw new NegativeValueException("Сумма для зачисления должна быть положительной");

            CashAmount += sum;
        }

        public void SpendFunds(double sum)
        {
            if (sum <= 0)
                throw new NegativeValueException("Сумма для списания должна быть положительной");

            if (sum > CashAmount)
                throw new OverdraftException("Операция отклонена: недостаточно средств");

            CashAmount -= sum;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Блок 1: Калькулятор деления \n");
            ExecuteSafeCalculator();

            Console.WriteLine("\n Блок 1 отклонен \n");
            Console.WriteLine("Нажмите любую клавишу для продолжения");
            Console.ReadKey();
            Console.Clear();

            Console.WriteLine("Блок 2: Управление кошельком клиента \n");
            ExecuteWalletManager();

            Console.WriteLine("\n Работа приложения завершена ");
            Console.ReadKey();
        }

        static void ExecuteSafeCalculator()
        {
            List<int> history = new List<int>();
            bool keepRunning = true;

            while (keepRunning)
            {
                try
                {
                    Console.Write("Введите делимое: ");
                    int dividend = int.Parse(Console.ReadLine());

                    Console.Write("Введите делитель: ");
                    int divisor = int.Parse(Console.ReadLine());

                    int quotient = dividend / divisor;

                    history.Add(quotient);

                    Console.WriteLine($"Частное: {quotient}");

                    Console.Write("Продолжить вычисления? (yes/no): ");
                    string response = Console.ReadLine().Trim().ToLower();
                    if (response != "yes")
                        keepRunning = false;
                }
                catch (DivideByZeroException)
                {
                    Console.WriteLine("Ошибка: попытка деления на ноль");
                }
                catch (FormatException)
                {
                    Console.WriteLine("Ошибка: требуется числовое значение");
                }
                finally
                {
                    Console.WriteLine("Итерация расчёта завершена");
                }
            }

            Console.WriteLine("\nЖурнал успешных операций:");
            for (int i = 0; i < history.Count; i++)
            {
                Console.WriteLine($"Запись {i + 1}: {history[i]}");
            }
        }

        static void ExecuteWalletManager()
        {
            ClientWallet wallet = null;

            while (wallet == null)
            {
                try
                {
                    Console.Write("Укажите начальную сумму (Enter для нуля): ");
                    string input = Console.ReadLine();
                    double startBalance = string.IsNullOrEmpty(input) ? 0 : double.Parse(input);
                    wallet = new ClientWallet(startBalance);
                    Console.WriteLine($"Кошелёк активирован. ID: {wallet.WalletId}, Доступно: {wallet.CashAmount:F2}");
                }
                catch (NegativeValueException ex)
                {
                    Console.WriteLine($"Ошибка: {ex.Message}");
                }
                catch (FormatException)
                {
                    Console.WriteLine("Ошибка: некорректный формат суммы");
                }
            }

            bool isActive = true;
            while (isActive)
            {
                try
                {
                    Console.WriteLine("\nМеню операций:");
                    Console.WriteLine("A: Пополнить кошелёк");
                    Console.WriteLine("B: Снять средства");
                    Console.WriteLine("C: Проверить баланс");
                    Console.WriteLine("D: Завершить сеанс");
                    Console.Write("Ваш выбор: ");
                    string choice = Console.ReadLine().ToUpper();

                    switch (choice)
                    {
                        case "A":
                            Console.Write("Сумма пополнения: ");
                            double addSum = double.Parse(Console.ReadLine());
                            wallet.AddFunds(addSum);
                            Console.WriteLine("Баланс обновлён");
                            break;

                        case "B":
                            Console.Write("Сумма снятия: ");
                            double spendSum = double.Parse(Console.ReadLine());
                            wallet.SpendFunds(spendSum);
                            Console.WriteLine("Операция одобрена");
                            break;

                        case "C":
                            break;

                        case "D":
                            isActive = false;
                            Console.WriteLine("Сеанс завершён.");
                            continue;

                        default:
                            Console.WriteLine("Неизвестная команда. Попробуйте ещё раз.");
                            continue;
                    }

                    Console.WriteLine($"Текущий остаток: {wallet.CashAmount:F2}");
                }
                catch (NegativeValueException ex)
                {
                    Console.WriteLine($"Ошибка транзакции: {ex.Message}");
                    Console.WriteLine($"Текущий остаток: {wallet.CashAmount:F2}");
                }
                catch (OverdraftException ex)
                {
                    Console.WriteLine($"Ошибка транзакции: {ex.Message}");
                    Console.WriteLine($"Текущий остаток: {wallet.CashAmount:F2}");
                }
                catch (FormatException)
                {
                    Console.WriteLine("Ошибка: ожидалось числовое значение");
                }
            }
        }
    }
}