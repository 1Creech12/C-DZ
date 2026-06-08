#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QFontDialog>
#include <QInputDialog>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QPrintDialog>
#include <QPrinter>
#include <QMessageBox>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Запрет изменения размера окна
    this->setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==================== МЕНЮ "ФАЙЛ" ====================

void MainWindow::on_action_New_triggered()
{
    ui->textEdit->clear();
    _filename.clear();
    this->setWindowTitle("Новый документ — Блокнот");
}

void MainWindow::on_action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Открыть файл", "",
                                                    "Все файлы (*.*);;Текстовые файлы (*.txt)");
    if (filename.isEmpty()) return;

    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        return;
    }

    QTextStream in(&file);
    ui->textEdit->setHtml(in.readAll());
    file.close();

    _filename = filename;
    this->setWindowTitle(filename + " — Блокнот");
}

void MainWindow::on_action_Save_triggered()
{
    if (_filename.isEmpty()) {
        on_action_SaveAs_triggered();
        return;
    }

    QFile file(_filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toHtml();
    out.flush();
    file.close();

    this->setWindowTitle(_filename + " — Блокнот");
}

void MainWindow::on_action_SaveAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить как", "",
                                                    "Все файлы (*.*);;Текстовые файлы (*.txt)");
    if (filename.isEmpty()) return;

    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toHtml();
    out.flush();
    file.close();

    _filename = filename;
    this->setWindowTitle(_filename + " — Блокнот");
}

void MainWindow::on_action_Print_triggered()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        ui->textEdit->print(&printer);
    }
}

void MainWindow::on_action_Exit_triggered()
{
    close();
}

// ==================== МЕНЮ "ПРАВКА" ====================

void MainWindow::on_action_Undo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_action_Redo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_action_Copy_triggered()
{
    _copytext = ui->textEdit->textCursor().selectedText();
    if (!_copytext.isEmpty()) {
        ui->textEdit->copy();
    }
}

void MainWindow::on_action_Cut_triggered()
{
    _copytext = ui->textEdit->textCursor().selectedText();
    if (!_copytext.isEmpty()) {
        ui->textEdit->cut();
    }
}

void MainWindow::on_action_Paste_triggered()
{
    if (!_copytext.isEmpty()) {
        ui->textEdit->textCursor().insertHtml(_copytext);
    } else {
        ui->textEdit->paste();
    }
}

void MainWindow::on_action_Delete_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (cursor.hasSelection()) {
        cursor.removeSelectedText();
    } else {
        cursor.deleteChar();
    }
}

void MainWindow::on_action_Date_triggered()
{
    QString date = QDate::currentDate().toString("dd.MM.yyyy");
    ui->textEdit->textCursor().insertText(date);
}

// ==================== МЕНЮ "ВИД" ====================

void MainWindow::on_action_Font_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        QTextCharFormat format;
        format.setFont(font);
        ui->textEdit->textCursor().setCharFormat(format);
    }
}

void MainWindow::on_action_Left_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_action_Center_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_action_Right_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

// ==================== МЕНЮ "НАЙТИ" ====================

void MainWindow::on_action_Search_triggered()
{
    bool ok;
    QString str = QInputDialog::getText(this, "Найти", "Введите текст:", QLineEdit::Normal, "", &ok);
    if (!ok || str.isEmpty()) return;

    QTextCursor oldCursor = ui->textEdit->textCursor();
    ui->textEdit->setTextCursor(QTextCursor(ui->textEdit->document()->findBlockByLineNumber(0)));

    bool finded = ui->textEdit->find(str);
    if (!finded) {
        ui->textEdit->setTextCursor(oldCursor);
        QMessageBox::information(this, "Поиск", "Текст не найден.");
    }
}

void MainWindow::on_action_Replace_triggered()
{
    bool ok1, ok2;
    QString findStr = QInputDialog::getText(this, "Заменить", "Что заменить:", QLineEdit::Normal, "", &ok1);
    if (!ok1 || findStr.isEmpty()) return;

    QString replaceStr = QInputDialog::getText(this, "Заменить", "На что заменить:", QLineEdit::Normal, "", &ok2);
    if (!ok2) return;

    QTextCursor oldCursor = ui->textEdit->textCursor();
    ui->textEdit->setTextCursor(QTextCursor(ui->textEdit->document()->findBlockByLineNumber(0)));

    int count = 0;
    while (ui->textEdit->find(findStr)) {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.insertText(replaceStr);
        count++;
    }

    if (count == 0) {
        ui->textEdit->setTextCursor(oldCursor);
        QMessageBox::information(this, "Замена", "Текст не найден.");
    } else {
        QMessageBox::information(this, "Замена", QString("Заменено %1 вхождений.").arg(count));
    }
}

void MainWindow::on_action_GoToLine_triggered()
{
    bool ok;
    int maxLine = ui->textEdit->document()->lineCount();
    int num = QInputDialog::getInt(this, "Перейти", "На строку:", 1, 1, maxLine, 1, &ok);

    if (ok) {
        QTextBlock block = ui->textEdit->document()->findBlockByLineNumber(num - 1);
        QTextCursor cursor(block);
        ui->textEdit->setTextCursor(cursor);
    }
}

// ==================== МЕНЮ "СПРАВКА" ====================

void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this, "О программе",
                       "Текстовый редактор\n"
                       "Версия 1.0\n\n"
                       "Лабораторная работа №8");
}