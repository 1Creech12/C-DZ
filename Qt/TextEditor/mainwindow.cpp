#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::on_textEdit_textChanged);

    ui->statusBar->showMessage("Готов к работе");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    app.newDocument();
    int idx = app.documentCount() - 1;
    ui->docList->addItem(QString("Новый %1").arg(idx + 1));
    ui->docList->setCurrentRow(idx);
    ui->statusBar->showMessage("Создан новый документ");
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (path.isEmpty()) return;

    app.newDocument();
    TextDocument* doc = dynamic_cast<TextDocument*>(app.getDocument(app.documentCount() - 1));
    if (doc) {
        doc->open(path);
    }

    QFileInfo fi(path);
    ui->docList->addItem(fi.fileName());
    ui->docList->setCurrentRow(app.documentCount() - 1);
    ui->statusBar->showMessage(QString("Открыт файл: %1").arg(path));
}

void MainWindow::on_actionSave_triggered()
{
    if (currentIndex < 0) {
        ui->statusBar->showMessage("Нет открытого документа");
        return;
    }

    TextDocument* doc = dynamic_cast<TextDocument*>(app.getDocument(currentIndex));
    if (!doc) return;

    doc->setContent(ui->textEdit->toPlainText());

    if (doc->getFilePath().isEmpty()) {
        QString path = QFileDialog::getSaveFileName(this, "Сохранить файл", "/Users/creech12/test", "Текстовые файлы (*.txt)");
        if (path.isEmpty()) return;
        doc->saveAs(path);
        QFileInfo fi(path);
        ui->docList->item(currentIndex)->setText(fi.fileName());
    } else {
        doc->save();
    }
    ui->statusBar->showMessage("Документ сохранён");
}

void MainWindow::on_actionClose_triggered()
{
    if (currentIndex < 0) return;

    TextDocument* doc = dynamic_cast<TextDocument*>(app.getDocument(currentIndex));
    if (doc && doc->getIsModified()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Закрыть", "Сохранить изменения?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            on_actionSave_triggered();
        } else if (reply == QMessageBox::Cancel) {
            return;
        }
    }

    app.closeDocument(currentIndex);
    delete ui->docList->takeItem(currentIndex);

    if (app.documentCount() == 0) {
        ui->textEdit->clear();
        ui->textEdit->setEnabled(false);
        currentIndex = -1;
    }

    ui->statusBar->showMessage("Документ закрыт");
}

void MainWindow::on_docList_currentRowChanged(int index)
{
    if (index < 0) return;

    if (currentIndex >= 0 && currentIndex < app.documentCount()) {
        TextDocument* prevDoc = dynamic_cast<TextDocument*>(app.getDocument(currentIndex));
        if (prevDoc && ui->textEdit->isEnabled()) {
            prevDoc->setContent(ui->textEdit->toPlainText());
        }
    }

    currentIndex = index;
    TextDocument* doc = dynamic_cast<TextDocument*>(app.getDocument(index));
    if (doc) {
        ui->textEdit->setPlainText(doc->getContent());
        ui->textEdit->setEnabled(true);
    }
}

void MainWindow::on_textEdit_textChanged()
{
    if (currentIndex >= 0 && currentIndex < app.documentCount()) {
        TextDocument* doc = dynamic_cast<TextDocument*>(app.getDocument(currentIndex));
        if (doc) {
            doc->setContent(ui->textEdit->toPlainText());
        }
    }
}

void MainWindow::on_actionGraphicEditor_triggered()
{
    GraphicWindow* w = new GraphicWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    ui->statusBar->showMessage("Открыт графический редактор");
}