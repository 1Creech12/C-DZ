#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->menuTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddToOrderClicked);

    populateMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateMenu()
{
    ui->menuTable->setRowCount(1);
    ui->menuTable->setItem(0, 0, new QTableWidgetItem("Борщ"));
    ui->menuTable->setItem(0, 1, new QTableWidgetItem("300"));
    ui->menuTable->setItem(0, 2, new QTableWidgetItem(QString::number(currentDishStock)));
}

void MainWindow::onAddToOrderClicked()
{
    int requestedQty = ui->quantitySpinBox->value();

    if (requestedQty > currentDishStock) {
        QMessageBox::warning(this, "Ошибка заказа",
                             "Недостаточно порций на кухне!\n"
                             "Доступно только: " + QString::number(currentDishStock));
        return;
    }

    currentDishStock -= requestedQty;

    ui->menuTable->item(0, 2)->setText(QString::number(currentDishStock));

    QMessageBox::information(this, "Успех",
                             "Блюдо успешно добавлено в заказ!\n"
                             "Количество: " + QString::number(requestedQty));
}