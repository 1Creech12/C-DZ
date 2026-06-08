#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>

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
    // Кнопки
    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_ac_clicked();
    void on_pushButton_dot_clicked();
    void on_pushButton_sign_clicked();

    // Операции
    void on_pushButton_plus_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_mult_clicked();
    void on_pushButton_div_clicked();
    void on_pushButton_eq_clicked();
    void on_pushButton_sin_clicked();
    void on_pushButton_ln_clicked();
    void on_pushButton_pow_clicked();
    void on_pushButton_inv_clicked();
    void on_pushButton_ms_clicked();
    void on_pushButton_mr_clicked();
    void on_pushButton_mc_clicked();
    void on_pushButton_mplus_clicked();
    void on_pushButton_mminus_clicked();

private:
    Ui::MainWindow *ui;
    QStack<QString> stack;
    double memory;

    void calculate(const QString &sgn);
};
#endif // MAINWINDOW_H