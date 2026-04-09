#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setValue(4);
    ui->spinBox_2->setValue(5);
    on_pushButton_2_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    int strok = ui->spinBox->value();
    int stolb = ui->spinBox_2->value();

    arr.clear();
    ui->tableWidget->setRowCount(strok);
    ui->tableWidget->setColumnCount(stolb);

    for (int i = 0; i < strok; ++i) {
        QVector<int> stroka;
        for (int j = 0; j < stolb; ++j) {
            int znachenie = QRandomGenerator::global()->bounded(10, 99);
            stroka.append(znachenie);
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString::number(znachenie)));
        }
        arr.append(stroka);
    }
    ui->textEdit->clear();
    ui->textEdit->append("Матрица создана.");

}

void MainWindow::on_pushButton_clicked()
{
    if (arr.isEmpty()) {
        ui->textEdit->setText("Сначала создайте матрицу");
        return;
    }
    ui->textEdit->clear();
    int rez = ui->comboBox->currentIndex();

    if (rez == 0) {
        ui->textEdit->append("Минимальное значение:");
    } else {
        ui->textEdit->append("Максимальное значение:");
    }

    for (int i = 0; i < arr.size(); ++i) {
        int result = arr[i][0]; // первый элемент строки

        for (int j = 1; j < arr[i].size(); ++j) {
            if (rez == 0) { // минимум
                if (arr[i][j] < result) {
                    result = arr[i][j];
                }
            } else { // максимум
                if (arr[i][j] > result) {
                    result = arr[i][j];
                }
            }
        }

        ui->textEdit->append("Строка " + QString::number(i + 1) + ": " + QString::number(result));
    }

}

