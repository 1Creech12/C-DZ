#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSwap_clicked();   // Кнопка "Поменять местами"
    void on_btnBrowse1_clicked(); // Кнопка "Обзор" для первого файла
    void on_btnBrowse2_clicked(); // Кнопка "Обзор" для второго файла

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H