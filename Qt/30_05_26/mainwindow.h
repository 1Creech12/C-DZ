#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddToOrderClicked();

private:
    Ui::MainWindow *ui;
    void populateMenu();

    int currentDishStock = 5;
};

#endif // MAINWINDOW_H