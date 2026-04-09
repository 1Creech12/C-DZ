#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fillRandomLists();
    displayLists();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillRandomLists(){
    list1.clear();
    list2.clear();
    for (int i = 0; i < 5; i++) {
        list1.append(QRandomGenerator::global()->bounded(1, 20));
        list2.append(QRandomGenerator::global()->bounded(1, 20));
    }
}

void MainWindow::displayLists(){
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->textEdit->append("Список 1: "+QString::number(list1.size())+" элементов");
    for (int val : list1)
        ui->textEdit->append(QString::number(val));
    ui->textEdit_2->append("\nСписок 2: "+QString::number(list2.size())+" элементов");
    for (int val : list2)
        ui->textEdit_2->append(QString::number(val));
}
void MainWindow::on_pushButton_clicked()
{
    bool ok;
    int value = ui->lineEdit->text().toInt(&ok);
    if (!ok){
        ui->textEdit->append("Ошибка");
        return;
    }
    if (ui->checkBox->isChecked())
        list1.append(value);
    if (ui->checkBox_2->isChecked())
        list2.append(value);

    displayLists();
    ui->lineEdit->clear();
}


void MainWindow::on_pushButton_2_clicked()
{
    fillRandomLists();
    displayLists();
}

