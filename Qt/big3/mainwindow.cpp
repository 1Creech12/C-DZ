#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>

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
    QString num1 = ui->lineEdit->text();
    QString num2 = ui->lineEdit_2->text();
    QString num3 = ui->lineEdit_3->text();

    int a = num1.toInt();
    int b = num2.toInt();
    int c = num3.toInt();

    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;

    int sum = 0;
    if (max = a){
        sum = c+b;
    } else if (max = b) {
        sum = a+c;
    } else {
        sum = a+b;
    }
    ui->label->setText("Сумма чисел: " + QString::number(sum));
}


void MainWindow::on_pushButton_2_clicked()
{
    QString num2_1 = ui->lineEdit_4->text();
    QString num2_2 = ui->lineEdit_5->text();

    int z = num2_1.toInt();
    int x = num2_2.toInt();

    if (z==x) {
        z = 0;
        x = 0;
        ui->lineEdit_4->setText(QString::number(z));
        ui->lineEdit_5->setText(QString::number(x));
    } else {
        int max2 = z;
        if (max2 < x) max2 = x;
        ui->lineEdit_4->setText(QString::number(max2));
        ui->lineEdit_5->setText(QString::number(max2));
    }
}

