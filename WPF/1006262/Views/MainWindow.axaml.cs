using System;
using System.Collections.Generic;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Media;
using _1006262.ViewModels;

namespace _1006262.Views;

public partial class MainWindow : Window
{
    private MainWindowViewModel? ViewModel => DataContext as MainWindowViewModel;
    private DateTime _startTime;
    private bool _isShiftPressed;
    private bool _isCapsLock;
    
    private Dictionary<Key, Border> _keyVisuals = new();
    private Dictionary<Key, string> _keyNormalChars = new();
    private Dictionary<Key, string> _keyShiftChars = new();

    public MainWindow()
    {
        InitializeComponent();
        InitializeKeyMappings();
    }

    private void InitializeKeyMappings()
    {
        _keyVisuals = new Dictionary<Key, Border>
        {
            { Key.D1, Key1 }, { Key.D2, Key2 }, { Key.D3, Key3 }, { Key.D4, Key4 },
            { Key.D5, Key5 }, { Key.D6, Key6 }, { Key.D7, Key7 }, { Key.D8, Key8 },
            { Key.D9, Key9 }, { Key.D0, Key0 },
            { Key.Q, KeyQ }, { Key.W, KeyW }, { Key.E, KeyE }, { Key.R, KeyR },
            { Key.T, KeyT }, { Key.Y, KeyY }, { Key.U, KeyU }, { Key.I, KeyI },
            { Key.O, KeyO }, { Key.P, KeyP },
            { Key.A, KeyA }, { Key.S, KeyS }, { Key.D, KeyD }, { Key.F, KeyF },
            { Key.G, KeyG }, { Key.H, KeyH }, { Key.J, KeyJ }, { Key.K, KeyK },
            { Key.L, KeyL },
            { Key.Z, KeyZ }, { Key.X, KeyX }, { Key.C, KeyC }, { Key.V, KeyV },
            { Key.B, KeyB }, { Key.N, KeyN }, { Key.M, KeyM },
            { Key.LeftShift, KeyLeftShift }, { Key.RightShift, KeyRightShift },
            { Key.CapsLock, KeyCapsLock }, { Key.Space, KeySpace }
        };

        _keyNormalChars = new Dictionary<Key, string>
        {
            { Key.D1, "1" }, { Key.D2, "2" }, { Key.D3, "3" }, { Key.D4, "4" },
            { Key.D5, "5" }, { Key.D6, "6" }, { Key.D7, "7" }, { Key.D8, "8" },
            { Key.D9, "9" }, { Key.D0, "0" },
            { Key.Q, "q" }, { Key.W, "w" }, { Key.E, "e" }, { Key.R, "r" },
            { Key.T, "t" }, { Key.Y, "y" }, { Key.U, "u" }, { Key.I, "i" },
            { Key.O, "o" }, { Key.P, "p" },
            { Key.A, "a" }, { Key.S, "s" }, { Key.D, "d" }, { Key.F, "f" },
            { Key.G, "g" }, { Key.H, "h" }, { Key.J, "j" }, { Key.K, "k" },
            { Key.L, "l" },
            { Key.Z, "z" }, { Key.X, "x" }, { Key.C, "c" }, { Key.V, "v" },
            { Key.B, "b" }, { Key.N, "n" }, { Key.M, "m" },
            { Key.Space, " " }
        };

        _keyShiftChars = new Dictionary<Key, string>
        {
            { Key.D1, "!" }, { Key.D2, "@" }, { Key.D3, "#" }, { Key.D4, "$" },
            { Key.D5, "%" }, { Key.D6, "^" }, { Key.D7, "&" }, { Key.D8, "*" },
            { Key.D9, "(" }, { Key.D0, ")" },
            { Key.Q, "Q" }, { Key.W, "W" }, { Key.E, "E" }, { Key.R, "R" },
            { Key.T, "T" }, { Key.Y, "Y" }, { Key.U, "U" }, { Key.I, "I" },
            { Key.O, "O" }, { Key.P, "P" },
            { Key.A, "A" }, { Key.S, "S" }, { Key.D, "D" }, { Key.F, "F" },
            { Key.G, "G" }, { Key.H, "H" }, { Key.J, "J" }, { Key.K, "K" },
            { Key.L, "L" },
            { Key.Z, "Z" }, { Key.X, "X" }, { Key.C, "C" }, { Key.V, "V" },
            { Key.B, "B" }, { Key.N, "N" }, { Key.M, "M" },
            { Key.Space, " " }
        };
    }

    private void MainWindow_KeyDown(object? sender, KeyEventArgs e)
    {
        HighlightKey(e.Key, true);

        if (e.Key == Key.LeftShift || e.Key == Key.RightShift)
        {
            _isShiftPressed = true;
            UpdateKeyboardLabels();
            return;
        }

        if (e.Key == Key.CapsLock)
        {
            _isCapsLock = !_isCapsLock;
            UpdateKeyboardLabels();
            return;
        }

        if (ViewModel == null || !ViewModel.IsRunning)
            return;

        string? keyChar = GetCharForKey(e.Key);
        if (keyChar != null)
        {
            ViewModel.AddInput(keyChar[0]);
        }

        e.Handled = true;
    }

    private void MainWindow_KeyUp(object? sender, KeyEventArgs e)
    {
        HighlightKey(e.Key, false);

        if (e.Key == Key.LeftShift || e.Key == Key.RightShift)
        {
            _isShiftPressed = false;
            UpdateKeyboardLabels();
        }

        e.Handled = true;
    }

    private void HighlightKey(Key key, bool isPressed)
    {
        if (_keyVisuals.TryGetValue(key, out var border))
        {
            border.Background = isPressed ? Brushes.LightBlue : Brushes.White;
        }
    }

    private void UpdateKeyboardLabels()
    {
        foreach (var kvp in _keyVisuals)
        {
            var key = kvp.Key;
            var border = kvp.Value;
            
            if (key == Key.LeftShift || key == Key.RightShift || 
                key == Key.CapsLock || key == Key.Space)
                continue;

            var textBlock = border.Child as TextBlock;
            if (textBlock == null)
                continue;

            bool isLetter = _keyNormalChars.ContainsKey(key) && 
                           char.IsLetter(_keyNormalChars[key][0]);
            
            string displayChar;
            if (isLetter)
            {
                displayChar = _isCapsLock ? 
                    _keyShiftChars[key] : _keyNormalChars[key];
            }
            else
            {
                displayChar = _isShiftPressed ? 
                    _keyShiftChars[key] : _keyNormalChars[key];
            }
            
            textBlock.Text = displayChar;
        }
    }

    private string? GetCharForKey(Key key)
    {
        if (!_keyNormalChars.ContainsKey(key))
            return null;

        bool isLetter = char.IsLetter(_keyNormalChars[key][0]);
        
        if (isLetter)
        {
            bool shouldUpper = _isCapsLock ^ _isShiftPressed;
            return shouldUpper ? _keyShiftChars[key] : _keyNormalChars[key];
        }
        else
        {
            return _isShiftPressed ? _keyShiftChars[key] : _keyNormalChars[key];
        }
    }
}