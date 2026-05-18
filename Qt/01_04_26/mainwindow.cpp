#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>

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

void MainWindow::displayStack(const QStack<int> &st, QTextEdit *textEdit)
{
    textEdit->clear();
    if (st.isEmpty()) return;

    // Копию для отображения сверху вниз
    QStack<int> temp = st;
    QStack<int> reversed;
    while (!temp.isEmpty()) {
        reversed.push(temp.pop());
    }

    int pos = 1;
    while (!reversed.isEmpty()) {
        int val = reversed.pop();
        textEdit->append(QString("Позиция %1: %2").arg(pos).arg(val));
        pos++;
    }
}

void MainWindow::on_fillButton_clicked()
{
    stack.clear();
    for (int i = 0; i < 10; ++i) {
        int randomValue = QRandomGenerator::global()->bounded(-10, 81); // [-10; 80]
        stack.push(randomValue);
    }
    displayStack(stack, ui->originalTextEdit);
    ui->resultTextEdit->clear();
}

void MainWindow::on_processButton_clicked()
{
    if (stack.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Стек пуст! Сначала заполните его.");
        return;
    }

    QStack<int> tempStack;
    int pos = 1;

    // Временный стек, заменяя значения
    while (!stack.isEmpty()) {
        int val = stack.pop();
        if (pos != 0) {
            val = val % pos;
        }
        tempStack.push(val);
        pos++;
    }

    // Обратно в исходный стек
    while (!tempStack.isEmpty()) {
        stack.push(tempStack.pop());
    }

    displayStack(stack, ui->resultTextEdit);
}

void MainWindow::on_clearButton_clicked()
{
    stack.clear();
    ui->originalTextEdit->clear();
    ui->resultTextEdit->clear();
}