#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

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

void MainWindow::displayQueue(const QQueue<int> &q, QTextEdit *textEdit)
{
    textEdit->clear();
    for (int i = 0; i < q.size(); ++i) {
        textEdit->append(QString("Позиция %1: %2").arg(i + 1).arg(q.at(i)));
    }
}

void MainWindow::on_fillButton_clicked()
{
    queue.clear();
    bool ok;
    for (int i = 0; i < 8; ++i) {
        int num = QInputDialog::getInt(this, "Ввод элемента", QString("Введите %1-й элемент:").arg(i + 1), 0, -2147483647, 2147483647, 1, &ok);
        if (!ok) {
            QMessageBox::warning(this, "Отмена", "Ввод прерван пользователем.");
            queue.clear();
            return;
        }
        queue.enqueue(num);
    }
    displayQueue(queue, ui->originalTextEdit);
    ui->resultTextEdit->clear();
}

void MainWindow::on_processButton_clicked()
{
    if (queue.size() != 8) {
        QMessageBox::warning(this, "Предупреждение", "В очереди должно быть ровно 8 элементов!");
        return;
    }

    // Исходные значения
    QVector<int> original;
    for (int i = 0; i < queue.size(); ++i) {
        original.append(queue.at(i));
    }

    // Очередь и сумма
    queue.clear();
    for (int i = 0; i < 4; ++i) {
        int sum = original[i] + original[7 - i];
        queue.enqueue(sum);
    }

    displayQueue(queue, ui->resultTextEdit);
}

void MainWindow::on_clearButton_clicked()
{
    queue.clear();
    ui->originalTextEdit->clear();
    ui->resultTextEdit->clear();
}