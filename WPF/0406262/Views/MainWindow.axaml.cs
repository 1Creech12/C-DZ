using System;
using System.Runtime.InteropServices;
using Avalonia.Controls;
using Avalonia.Interactivity;

namespace _0406262.Views
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void OnGetDiagonalClick(object? sender, RoutedEventArgs e)
        {
            double diagonalInches = 0;

            if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
            {
                diagonalInches = GetMacOSMonitorDiagonal();
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                diagonalInches = GetWindowsMonitorDiagonal();
            }
            else
            {
                ResultText.Text = "Для данной ОС не реализовано";
                return;
            }

            if (diagonalInches > 0)
            {
                ResultText.Text = $"Диагональ монитора:\n{diagonalInches:F1} дюймов";
            }
            else
            {
                ResultText.Text = "Не удалось получить данные о мониторе";
            }
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct CGSize
        {
            public double Width;
            public double Height;
        }

        [DllImport("/System/Library/Frameworks/CoreGraphics.framework/CoreGraphics")]
        private static extern CGSize CGDisplayScreenSize(uint display);

        [DllImport("/System/Library/Frameworks/CoreGraphics.framework/CoreGraphics")]
        private static extern uint CGMainDisplayID();

        private double GetMacOSMonitorDiagonal()
        {
            try
            {
                uint mainDisplay = CGMainDisplayID();
                CGSize size = CGDisplayScreenSize(mainDisplay);

                double widthInches = size.Width / 25.4;
                double heightInches = size.Height / 25.4;

                return Math.Sqrt(widthInches * widthInches + heightInches * heightInches);
            }
            catch
            {
                return 0;
            }
        }

        [DllImport("user32.dll")]
        private static extern IntPtr GetDC(IntPtr hwnd);

        [DllImport("user32.dll")]
        private static extern int ReleaseDC(IntPtr hwnd, IntPtr hdc);

        [DllImport("gdi32.dll")]
        private static extern int GetDeviceCaps(IntPtr hdc, int nIndex);

        private const int HORZSIZE = 4;
        private const int VERTSIZE = 6;

        private double GetWindowsMonitorDiagonal()
        {
            try
            {
                IntPtr hdc = GetDC(IntPtr.Zero);
                if (hdc != IntPtr.Zero)
                {
                    int widthMm = GetDeviceCaps(hdc, HORZSIZE);
                    int heightMm = GetDeviceCaps(hdc, VERTSIZE);
                    ReleaseDC(IntPtr.Zero, hdc);

                    double widthInches = widthMm / 25.4;
                    double heightInches = heightMm / 25.4;

                    return Math.Sqrt(widthInches * widthInches + heightInches * heightInches);
                }
            }
            catch { }
            return 0;
        }
    }
}