#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>

class QTextEdit;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fillButton_clicked();
    void on_processButton_clicked();
    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    QQueue<int> queue;
    void displayQueue(const QQueue<int> &q, QTextEdit *textEdit);
};

#endif // MAINWINDOW_H