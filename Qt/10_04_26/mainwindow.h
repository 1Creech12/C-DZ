#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QMap>
#include <QString>
#include <QMessageBox>

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
    void on_addClassButton_clicked();
    void on_analyzeButton_clicked();
    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    QMap<QString, QSet<QString>> classGirls;
    QSet<QString> allGirlNames;

    void updateClassList();
    void analyzeNames();
    void clearAll();
};

#endif // MAINWINDOW_H