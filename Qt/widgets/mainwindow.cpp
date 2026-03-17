#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
    ui->label->setText(ui->lineEdit->text());
    ui->label->setStyleSheet("color: blue ;"
                            "font-family: Comic Sans MS;"
                            "font-size: 20px");
    ui->lineEdit->clear();
}

