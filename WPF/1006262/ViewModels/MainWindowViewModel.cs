using System;
using System.Text;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace _1006262.ViewModels;

public partial class MainWindowViewModel : ObservableObject
{
    [ObservableProperty]
    private string _targetText = "";

    [ObservableProperty]
    private string _userInputText = "";

    [ObservableProperty]
    private int _errors;

    [ObservableProperty]
    private int _length = 10;

    [ObservableProperty]
    private bool _useCase;

    [ObservableProperty]
    private bool _isRunning;

    [ObservableProperty]
    private double _speed;

    [ObservableProperty]
    private int _inputLength;

    public bool CanStart => !IsRunning;
    public bool CanStop => IsRunning;

    private StringBuilder _userInput = new();
    private DateTime _startTime;

    public MainWindowViewModel()
    {
    }

    [RelayCommand(CanExecute = nameof(CanStart))]
    private void Start()
    {
        IsRunning = true;
        Errors = 0;
        Speed = 0;
        InputLength = 0;
        _userInput.Clear();
        UserInputText = "";
        GenerateTargetText();
        
        // Уведомляем о изменении CanExecute для команд
        StartCommand.NotifyCanExecuteChanged();
        StopCommand.NotifyCanExecuteChanged();
    }

    [RelayCommand(CanExecute = nameof(CanStop))]
    private void Stop()
    {
        IsRunning = false;
        TargetText = "";
        UserInputText = "";
        _userInput.Clear();
        InputLength = 0;
        
        StartCommand.NotifyCanExecuteChanged();
        StopCommand.NotifyCanExecuteChanged();
    }

    private void GenerateTargetText()
    {
        const string lowerChars = "abcdefghijklmnopqrstuvwxyz";
        const string upperChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const string digits = "1234567890";
        
        string pool = lowerChars + digits;
        if (UseCase)
            pool += upperChars;

        var random = new Random();
        var result = new char[Length];
        for (int i = 0; i < Length; i++)
        {
            result[i] = pool[random.Next(pool.Length)];
        }
        TargetText = new string(result);
    }

    public void AddInput(char c)
    {
        if (!IsRunning || string.IsNullOrEmpty(TargetText))
            return;

        _userInput.Append(c);
        InputLength = _userInput.Length;
        UserInputText = _userInput.ToString();
        
        // Проверяем правильность ввода
        int currentIndex = _userInput.Length - 1;
        if (currentIndex < TargetText.Length)
        {
            if (c != TargetText[currentIndex])
            {
                Errors++;
            }
        }

        // Вычисляем скорость
        if (_userInput.Length == 1)
            _startTime = DateTime.Now;
        
        double elapsed = (DateTime.Now - _startTime).TotalSeconds;
        if (elapsed > 0)
            Speed = _userInput.Length / elapsed;

        // Проверяем завершение
        if (_userInput.Length >= TargetText.Length)
        {
            IsRunning = false;
            StartCommand.NotifyCanExecuteChanged();
            StopCommand.NotifyCanExecuteChanged();
        }
    }
}