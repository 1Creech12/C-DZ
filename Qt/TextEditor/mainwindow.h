#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "application.h"
#include "textdocument.h"

namespace Ui {
class MainWindow;
}

class TextApplication : public Application
{
    Q_OBJECT

protected:
    document* createDocument() override { return new TextDocument(); }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* ui;
    TextApplication app;
    int currentIndex = -1;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionClose_triggered();
    void on_actionGraphicEditor_triggered();
    void on_docList_currentRowChanged(int index);
    void on_textEdit_textChanged();
};

#endif