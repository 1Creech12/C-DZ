#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString firstNumStr = ui->lineEdit->text(); QString secondNumStr = ui->lineEdit_2->text(); //Получаем текст из первой
    //и второй строк
    bool ok;
    /*Проводим проверку на ввод недопустимых символов (например, если
пользователь не ввел число, ввел буквы или отрицательное число). Для этого
переводим полученный текст в вещественное число и заносим в переменную
вещественного типа. В случае ошибки выводится информационное окно класса
QMessageBox*/
    float firstNum = firstNumStr.toFloat(&ok);
    if (!ok) {
        QMessageBox::information(this,"Ошибка", "Введите число!");
        return; }
    float secondNum = secondNumStr.toFloat(&ok);
    if (!ok) {
        QMessageBox::information(this,"Ошибка", "Введите число!");
        return; }

    if (secondNum <= 0 || firstNum <= 0) {
        QMessageBox::information(this,"Ошибка", "Отрицательное число!");
        return; }
    //Создаем переменную для хранения результата
    float result = firstNum * secondNum;
    //Переводим результат в строку и записываем в виджет lineEdit_3
    ui->lineEdit_3->setText(QString::number(result));
}

