#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnBrowse1_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите первый файл", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (!fileName.isEmpty()) {
        ui->lineEditFile1->setText(fileName);
    }
}

void MainWindow::on_btnBrowse2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите второй файл", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (!fileName.isEmpty()) {
        ui->lineEditFile2->setText(fileName);
    }
}

void MainWindow::on_btnSwap_clicked()
{
    QString pathF1 = ui->lineEditFile1->text();
    QString pathF2 = ui->lineEditFile2->text();

    if (pathF1.isEmpty() || pathF2.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Укажите пути к обоим файлам!");
        return;
    }

    QFile fileF1(pathF1);
    QFile fileF2(pathF2);

    if (!fileF1.exists()) {
        QMessageBox::warning(this, "Ошибка", "Файл 1 не найден:\n" + pathF1);
        return;
    }
    if (!fileF2.exists()) {
        QMessageBox::warning(this, "Ошибка", "Файл 2 не найден:\n" + pathF2);
        return;
    }

    QFileInfo infoF1(pathF1);
    QString pathH = infoF1.absolutePath() + "/_temp_swap_h.txt";
    QFile fileH(pathH);

    if (!fileF1.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не могу открыть файл 1 для чтения:\n" + pathF1);
        return;
    }
    QTextStream inF1(&fileF1);
    QString contentF1 = inF1.readAll();
    fileF1.close();

    if (!fileH.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не могу создать временный файл:\n" + pathH);
        return;
    }
    QTextStream outH(&fileH);
    outH << contentF1;
    fileH.close();

    // 2
    if (!fileF2.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не могу открыть файл 2 для чтения:\n" + pathF2);
        return;
    }
    QTextStream inF2(&fileF2);
    QString contentF2 = inF2.readAll();
    fileF2.close();

    if (!fileF1.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не могу открыть файл 1 для записи:\n" + pathF1);
        return;
    }
    QTextStream outF1(&fileF1);
    outF1 << contentF2;
    fileF1.close();

    // 3
    if (!fileH.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не могу открыть временный файл для чтения:\n" + pathH);
        return;
    }
    QTextStream inH(&fileH);
    QString contentH = inH.readAll();
    fileH.close();

    if (!fileF2.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не могу открыть файл 2 для записи:\n" + pathF2);
        return;
    }
    QTextStream outF2(&fileF2);
    outF2 << contentH;
    fileF2.close();

    QFile::remove(pathH);

    if (fileF1.open(QIODevice::ReadOnly)) {
        QTextStream showF1(&fileF1);
        ui->textEditContent1->setPlainText(showF1.readAll());
        fileF1.close();
    }
    if (fileF2.open(QIODevice::ReadOnly)) {
        QTextStream showF2(&fileF2);
        ui->textEditContent2->setPlainText(showF2.readAll());
        fileF2.close();
    }

    QMessageBox::information(this, "Готово", "Содержимое файлов успешно поменяно местами!");
}