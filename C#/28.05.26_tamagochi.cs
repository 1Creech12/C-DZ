using System;
using System.Timers;
using System.Collections.Generic;
using System.Threading;

namespace Tamagotchi
{
    public delegate void RequestHandler(string request);

    public class StateContainer<T>
    {
        public T Value { get; set; }
        public StateContainer(T value)
        {
            Value = value;
        }
    }

    // Петомец с состояниями и т.д
    public class Pet
    {
        private List<string> requests = new List<string> { "Покормить", "Погулять", "Уложить спать", "Полечить", "Поиграть" };
        private string lastRequest = "";
        private string currentRequest = "";
        private Random random = new Random();
        private int missedRequests = 0;
        private int wrongActions = 0;
        private bool isSick = false;
        private bool isDead = false;
        private System.Timers.Timer requestTimer;
        private System.Timers.Timer lifeTimer;
        private object lockObj = new object();

        public event RequestHandler OnRequest;
        public event Action OnDeath;

        public StateContainer<string> Name { get; set; }
        public string CurrentRequest => currentRequest;

        public Pet(string name)
        {
            Name = new StateContainer<string>(name);
            DrawPet("normal");

            // Сначала создаем таймеры
            requestTimer = new System.Timers.Timer(15000);
            requestTimer.Elapsed += OnRequestTimeout;
            requestTimer.AutoReset = false;

            lifeTimer = new System.Timers.Timer(120000);
            lifeTimer.Elapsed += OnLifeTimeEnd;
            lifeTimer.AutoReset = false;
            lifeTimer.Start();

            GenerateNewRequest();

            if (OnRequest != null)
            {
                OnRequest(currentRequest);
            }
        }

        // Таймер жизни
        private void OnLifeTimeEnd(object sender, ElapsedEventArgs e)
        {
            if (!isDead)
            {
                Die("Время жизни истекло! Питомец умер от старости.");
            }
        }

        // Генерация новой просьбы
        private void GenerateNewRequest()
        {
            string newRequest;
            do
            {
                newRequest = requests[random.Next(requests.Count)];
            } while (newRequest == lastRequest && requests.Count > 1);

            lastRequest = newRequest;
            currentRequest = newRequest;
            wrongActions = 0;

            ResetRequestTimer();
        }

        // Сброс таймера просьбы
        private void ResetRequestTimer()
        {
            requestTimer.Stop();
            requestTimer.Start();
        }

        // Таймер просьбы
        private void OnRequestTimeout(object sender, ElapsedEventArgs e)
        {
            if (isDead) return;

            lock (lockObj)
            {
                missedRequests++;
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine($"\nВремя вышло! Просьба пропущена. Пропусков: {missedRequests}/3");
                Console.ResetColor();

                if (CheckMissedRequests())
                {
                    return;
                }

                GenerateNewRequest();

                if (OnRequest != null)
                {
                    OnRequest(currentRequest);
                }
            }
        }

        private void MakeRequest(object sender, ElapsedEventArgs e)
        {
            // Заглушка
        }

        // Обработка действия пользователя
        public void SatisfyRequest(string request)
        {
            lock (lockObj)
            {
                if (isDead) return;
                // Проверка просьбы
                if (request == currentRequest)
                {
                    if (isSick && request == "Полечить")
                    {
                        isSick = false;
                        missedRequests = 0;
                        DrawPet("normal");
                        Console.ForegroundColor = ConsoleColor.Green;
                        Console.WriteLine($"\nВы вылечили {Name.Value}!");
                        Console.ResetColor();
                    }
                    else if (!isSick)
                    {
                        missedRequests = 0;
                        DrawPet("happy");
                        Console.ForegroundColor = ConsoleColor.Green;
                        Console.WriteLine($"\n{Name.Value} очень доволен!");
                        Console.ResetColor();
                        Thread.Sleep(1000);
                        DrawPet("normal");
                    }

                    GenerateNewRequest();
                    
                    if (OnRequest != null)
                    {
                        OnRequest(currentRequest);
                    }
                }
                else
                {
                    wrongActions++;
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.WriteLine($"\nНеверно! ({wrongActions}/3) {Name.Value} просит: {currentRequest}");
                    Console.ResetColor();

                    if (wrongActions >= 3)
                    {
                        missedRequests++;
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine($"Три неверных действия! Просьба пропущена. Пропусков: {missedRequests}/3");
                        Console.ResetColor();
                        
                        if (CheckMissedRequests())
                        {
                            return;
                        }

                        GenerateNewRequest();
                        
                        if (OnRequest != null)
                        {
                            OnRequest(currentRequest);
                        }
                    }
                    else
                    {

                        Console.WriteLine($"Осталось попыток: {3 - wrongActions}");
                    }
                }
            }
        }

        // Пропустить просьбу
        public void IgnoreRequest()
        {
            lock (lockObj)
            {
                if (isDead) return;

                missedRequests++;
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine($"\nПросьба пропущена. Пропусков: {missedRequests}/3");
                Console.ResetColor();

                if (CheckMissedRequests())
                {
                    return;
                }

                GenerateNewRequest();
                
                if (OnRequest != null)
                {
                    OnRequest(currentRequest);
                }
            }
        }

        // Проверка количества пропущенных просьб и состояния здоровья
        private bool CheckMissedRequests()
        {
            if (missedRequests >= 3 && !isSick)
            {
                isSick = true;
                DrawPet("sick");
                currentRequest = "Полечить";
                lastRequest = "Полечить";
                wrongActions = 0;
                
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine($"\n{Name.Value} заболел! Нужно полечить!");
                Console.ResetColor();

                ResetRequestTimer();
                return false;
            }
            else if (isSick && missedRequests >= 4)
            {
                Die("Питомец умер");
                return true;
            }
            return false;
        }

        private void Die(string message)
        {
            isDead = true;
            requestTimer.Stop();
            lifeTimer.Stop();
            DrawPet("dead");

            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine($"\n{message}");
            Console.ResetColor();

            if (OnDeath != null)
            {
                OnDeath();
            }

            Thread.Sleep(3000);
            Environment.Exit(0);
        }

        private void DrawPet(string state)
        {
            Console.Clear();
            
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine($"{Name.Value}");
            Console.ResetColor();

            Console.WriteLine();
            
            switch (state)
            {
                case "normal":
                    Console.WriteLine("     /\\_/\\   ");
                    Console.WriteLine("    ( o.o )  ");
                    Console.WriteLine("     > ^ <   ");
                    break;
                case "happy":
                    Console.ForegroundColor = ConsoleColor.Green;
                    Console.WriteLine("     /\\_/\\   ");
                    Console.WriteLine("    ( ^.^ )  ");
                    Console.WriteLine("     > ^ <   ");
                    Console.ResetColor();
                    break;
                case "sad":
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.WriteLine("     /\\_/\\   ");
                    Console.WriteLine("    ( T.T )  ");
                    Console.WriteLine("     > ^ <   ");
                    Console.ResetColor();
                    break;
                case "sick":
                    Console.ForegroundColor = ConsoleColor.Magenta;
                    Console.WriteLine("     /\\_/\\   ");
                    Console.WriteLine("    ( x.x )  ");
                    Console.WriteLine("     > ^ <   ");
                    Console.ResetColor();
                    break;
                case "dead":
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("     /\\_/\\   ");
                    Console.WriteLine("    ( X.X )  ");
                    Console.WriteLine("     > _ <   ");
                    Console.ResetColor();
                    break;
            }
            Console.WriteLine();
            
            if (isSick && state != "dead")
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("Внимание: Питомец болен!");
                Console.ResetColor();
            }

            if (!isDead)
            {
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine($"\nТекущая просьба: {currentRequest}");
                Console.ResetColor();
            }
        }
    }

    class Program
    {
        static Pet pet;

        static void Main(string[] args)
        {
            Console.Title = "Тамагочи";
            
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("\t\tТамагочи");
            Console.ResetColor();
            
            Console.Write("\nВведите имя питомца: ");
            string name = Console.ReadLine();

            if (string.IsNullOrWhiteSpace(name))
                name = "Тама";

            pet = new Pet(name);

            pet.OnRequest += HandleRequest;
            pet.OnDeath += HandleDeath;

            DrawControls();

            while (true)
            {
                if (Console.KeyAvailable)
                {
                    var key = Console.ReadKey(true).Key;

                    if (key == ConsoleKey.Escape)
                    {
                        Console.Clear();
                        Console.WriteLine("\nПока");
                        Thread.Sleep(1000);
                        break;
                    }

                    string action = "";
                    switch (key)
                    {
                        case ConsoleKey.D1: action = "Покормить"; break;
                        case ConsoleKey.D2: action = "Погулять"; break;
                        case ConsoleKey.D3: action = "Уложить спать"; break;
                        case ConsoleKey.D4: action = "Полечить"; break;
                        case ConsoleKey.D5: action = "Поиграть"; break;
                        case ConsoleKey.D0:
                            pet.IgnoreRequest();
                            continue;
                        default:
                            continue;
                    }

                    pet.SatisfyRequest(action);
                }

                Thread.Sleep(100);
            }
        }

        static void DrawControls()
        {
            Console.WriteLine("\nУправление:");
            Console.WriteLine(" 1 - Покормить");
            Console.WriteLine(" 2 - Погулять");
            Console.WriteLine(" 3 - Уложить спать");
            Console.WriteLine(" 4 - Полечить");
            Console.WriteLine(" 5 - Поиграть");
            Console.WriteLine(" 0 - Пропустить просьбу");
            Console.WriteLine(" ESC - Выход");
        }

        static void HandleRequest(string request)
        {
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine($"\n{pet.Name.Value} просит: {request}");
            Console.WriteLine("Выберите действие (1-5) или 0 для пропуска:");
            Console.ResetColor();
        }

        static void HandleDeath()
        {
            Console.WriteLine("\nНажмите любую клавишу для выхода");
            Console.ReadKey();
        }
    }
}