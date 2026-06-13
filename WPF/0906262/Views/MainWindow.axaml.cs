using Avalonia.Controls;
using Avalonia.Interactivity;

namespace _0906262.Views
{
    public partial class MainWindow : Window
    {
        private string _currentNumber = "0";
        private string _previousOperation = "";
        private double _previousValue = 0;
        private string _currentOperator = "";
        private bool _isNewEntry = true;

        public MainWindow()
        {
            InitializeComponent();
            UpdateDisplay();
        }

        private void UpdateDisplay()
        {
            PreviousOperationTextBox.Text = _previousOperation;
            CurrentNumberTextBox.Text = _currentNumber;
        }

        private void Digit_Click(object? sender, RoutedEventArgs e)
        {
            if (sender is Button button && button.Tag is string digit)
            {
                if (_isNewEntry)
                {
                    _currentNumber = digit;
                    _isNewEntry = false;
                }
                else
                {
                    if (_currentNumber == "0" && digit == "0")
                        return;
                    
                    if (_currentNumber == "0" && digit != "0")
                    {
                        _currentNumber = digit;
                    }
                    else
                    {
                        _currentNumber += digit;
                    }
                }
                UpdateDisplay();
            }
        }

        private void Decimal_Click(object? sender, RoutedEventArgs e)
        {
            if (_isNewEntry)
            {
                _currentNumber = "0.";
                _isNewEntry = false;
            }
            else if (!_currentNumber.Contains("."))
            {
                _currentNumber += ".";
            }
            UpdateDisplay();
        }

        private void Operator_Click(object? sender, RoutedEventArgs e)
        {
            if (sender is Button button && button.Tag is string op)
            {
                if (double.TryParse(_currentNumber, out double currentValue))
                {
                    if (_currentOperator != "" && !_isNewEntry)
                    {
                        Calculate();
                    }
                    
                    _previousValue = currentValue;
                    _currentOperator = op;
                    _previousOperation = $"{_currentNumber} {op}";
                    _isNewEntry = true;
                    UpdateDisplay();
                }
            }
        }

        private void Equals_Click(object? sender, RoutedEventArgs e)
        {
            if (_currentOperator != "" && double.TryParse(_currentNumber, out double currentValue))
            {
                Calculate();
                _previousOperation = "";
                _currentOperator = "";
                _isNewEntry = true;
                UpdateDisplay();
            }
        }

        private void Calculate()
        {
            if (double.TryParse(_currentNumber, out double currentValue))
            {
                double result = 0;
                switch (_currentOperator)
                {
                    case "+":
                        result = _previousValue + currentValue;
                        break;
                    case "-":
                        result = _previousValue - currentValue;
                        break;
                    case "*":
                        result = _previousValue * currentValue;
                        break;
                    case "/":
                        if (currentValue == 0)
                        {
                            _currentNumber = "Ошибка";
                            _isNewEntry = true;
                            return;
                        }
                        result = _previousValue / currentValue;
                        break;
                }
                
                _currentNumber = result.ToString("G15");
            }
        }

        private void ClearEntry_Click(object? sender, RoutedEventArgs e)
        {
            _currentNumber = "0";
            _isNewEntry = true;
            UpdateDisplay();
        }

        private void ClearAll_Click(object? sender, RoutedEventArgs e)
        {
            _currentNumber = "0";
            _previousOperation = "";
            _previousValue = 0;
            _currentOperator = "";
            _isNewEntry = true;
            UpdateDisplay();
        }

        private void Backspace_Click(object? sender, RoutedEventArgs e)
        {
            if (_isNewEntry || _currentNumber == "Ошибка")
            {
                _currentNumber = "0";
                _isNewEntry = true;
                UpdateDisplay();
                return;
            }

            if (_currentNumber.Length > 1)
            {
                _currentNumber = _currentNumber.Substring(0, _currentNumber.Length - 1);
            }
            else
            {
                _currentNumber = "0";
                _isNewEntry = true;
            }
            UpdateDisplay();
        }
    }
}