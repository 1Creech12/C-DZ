using System;
using System.Collections.Generic;
using System.Threading;

namespace GrandPrix
{
    public delegate void StatusUpdateHandler(string statusInfo);
    public delegate void VictoryHandler(string championName);

    public abstract class Racer
    {
        public string Model { get; set; }
        public int Distance { get; set; }
        public int Velocity { get; set; }
        
        public event StatusUpdateHandler OnStatusUpdate;
        public event VictoryHandler OnVictory;

        public Racer(string model)
        {
            Model = model;
            Distance = 0;
            Random generator = new Random();
            Velocity = generator.Next(10, 30); 
        }

        public abstract void Advance();

        protected void BroadcastStatus(string info)
        {
            OnStatusUpdate?.Invoke(info);
        }

        protected void DeclareVictory()
        {
            OnVictory?.Invoke(Model);
        }
    }

    public class RacingCar : Racer
    {
        public RacingCar() : base("Гоночный болид") { }

        public override void Advance()
        {
            Random generator = new Random();
            Velocity += generator.Next(-5, 10);
            
            NormalizeSpeed(1, 50);

            Distance += Velocity;
            BroadcastStatus($"[Болид] {Model} преодолел {Distance} км. Текущая скорость: {Velocity} км/ч");
            
            if (Distance >= 100) DeclareVictory();
        }

        private void NormalizeSpeed(int min, int max)
        {
            if (Velocity < min) Velocity = min;
            if (Velocity > max) Velocity = max;
        }
    }

    public class Sedan : Racer
    {
        public Sedan() : base("Седан") { }

        public override void Advance()
        {
            Random generator = new Random();
            Velocity += generator.Next(-3, 5);
            if (Velocity < 1) Velocity = 1;

            Distance += Velocity;
            BroadcastStatus($"[Седан] {Model} проехал {Distance} км. Скорость: {Velocity} км/ч");

            if (Distance >= 100) DeclareVictory();
        }
    }

    public class Lorry : Racer
    {
        public Lorry() : base("Фура") { }

        public override void Advance()
        {
            Random generator = new Random();
            Velocity += generator.Next(-2, 3);
            if (Velocity < 1) Velocity = 1;

            Distance += Velocity;

            Distance = Math.Min(Distance, 100);

            BroadcastStatus($"[Фура] {Model} проехала {Distance} км. Скорость: {Velocity} км/ч");
            
            if (Distance >= 100) DeclareVictory();
        }
    }

    public class Minibus : Racer
    {
        public Minibus() : base("Микроавтобус") { }

        public override void Advance()
        {
            Random generator = new Random();
            int acceleration = generator.Next(-4, 6);
            Velocity += acceleration;

            Distance += Velocity;
            BroadcastStatus($"[Микроавтобус] {Model} проехал {Distance} км. Скорость: {Velocity} км/ч");

            if (Distance >= 100) DeclareVictory();
        }
    }

    public class Tournament
    {
        private List<Racer> participants = new List<Racer>();
        private bool competitionFinished = false;
        private int roundCount = 0; // Счетчик раундов

        public void RegisterRacer(Racer racer)
        {
            racer.OnStatusUpdate += DisplayStatus;
            racer.OnVictory += AnnounceChampion;
            participants.Add(racer);
        }

        private void DisplayStatus(string message)
        {
            if (!competitionFinished)
                Console.WriteLine($"Раунд {roundCount}: {message}");
        }

        private void AnnounceChampion(string championModel)
        {
            if (!competitionFinished)
            {
                competitionFinished = true;
                Console.WriteLine("  Финиш");
                Console.WriteLine($"  Победитель: {championModel}");
                Console.WriteLine($"  Всего раундов: {roundCount}");
            }
        }

        public void BeginTournament()
        {
            Console.WriteLine("Гран-при");
            Console.WriteLine("Нажмите Enter для старта");
            Console.ReadLine();
            Console.Clear();

            while (!competitionFinished)
            {
                roundCount++;
                Console.WriteLine($"\nРаунд {roundCount}");
                
                foreach (var racer in participants)
                {
                    if (!competitionFinished)
                    {
                        racer.Advance();
                    }
                }
                
                Thread.Sleep(700);
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Tournament tournament = new Tournament();
            
            tournament.RegisterRacer(new RacingCar());
            tournament.RegisterRacer(new Sedan());
            tournament.RegisterRacer(new Lorry());
            tournament.RegisterRacer(new Minibus());
            
            tournament.BeginTournament();

            Console.WriteLine("\nГонка завершена!");
            Console.ReadLine();
        }
    }
}