#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , memory(0.0)
{
    ui->setupUi(this);

    ui->lineEdit->setMaxLength(10);
    ui->lineEdit->setAlignment(Qt::AlignRight);
    QFont font = ui->lineEdit->font();
    font.setPointSize(16);
    ui->lineEdit->setFont(font);
    ui->lineEdit->setEnabled(false);

    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_2->setAlignment(Qt::AlignRight);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_0_clicked() { ui->lineEdit->insert("0"); }
void MainWindow::on_pushButton_1_clicked() { ui->lineEdit->insert("1"); }
void MainWindow::on_pushButton_2_clicked() { ui->lineEdit->insert("2"); }
void MainWindow::on_pushButton_3_clicked() { ui->lineEdit->insert("3"); }
void MainWindow::on_pushButton_4_clicked() { ui->lineEdit->insert("4"); }
void MainWindow::on_pushButton_5_clicked() { ui->lineEdit->insert("5"); }
void MainWindow::on_pushButton_6_clicked() { ui->lineEdit->insert("6"); }
void MainWindow::on_pushButton_7_clicked() { ui->lineEdit->insert("7"); }
void MainWindow::on_pushButton_8_clicked() { ui->lineEdit->insert("8"); }
void MainWindow::on_pushButton_9_clicked() { ui->lineEdit->insert("9"); }
void MainWindow::on_pushButton_ac_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    stack.clear();
}

void MainWindow::on_pushButton_dot_clicked()
{
    QString text = ui->lineEdit->text();
    if (text.length() == 0 ||
        text.at(text.length() - 1) == '-' ||
        text.indexOf('.') != -1)
        return;
    ui->lineEdit->setText(text + '.');
}

void MainWindow::on_pushButton_sign_clicked()
{
    QString text = ui->lineEdit->text();
    if (text.length() == 0 || text.at(0) != '-')
        ui->lineEdit->setText("-" + text);
    else
        ui->lineEdit->setText(text.remove(0, 1));
}

void MainWindow::on_pushButton_plus_clicked()  { calculate("+"); }
void MainWindow::on_pushButton_minus_clicked() { calculate("-"); }
void MainWindow::on_pushButton_mult_clicked()  { calculate("*"); }
void MainWindow::on_pushButton_div_clicked()   { calculate("/"); }

void MainWindow::calculate(const QString &sgn)
{
    if (ui->lineEdit->text().length() == 0) {
        return;
    }

    if (stack.length() >= 2) {
        double val2 = ui->lineEdit->text().toDouble();
        QString sign = stack.pop();
        double val1 = stack.pop().toDouble();

        if (sign == "+") {
            stack.push(QString::number(val1 + val2));
        } else if (sign == "-") {
            stack.push(QString::number(val1 - val2));
        } else if (sign == "*") {
            stack.push(QString::number(val1 * val2));
        } else if (sign == "/") {
            if (val2 == 0) {
                stack.push(QString::number(val1));
            } else {
                stack.push(QString::number(val1 / val2));
            }
        }
        stack.push(sgn);
    } else {
        stack.push(ui->lineEdit->text());
        stack.push(sgn);
    }

    ui->lineEdit->clear();
    ui->lineEdit_2->setText(stack.toList().join(""));
}

void MainWindow::on_pushButton_eq_clicked()
{
    if (ui->lineEdit->text().length() != 0 && stack.length() == 2) {
        stack.push(ui->lineEdit->text());
    }

    if (stack.length() < 3) {
        return;
    }

    double val2 = stack.pop().toDouble();
    QString sign = stack.pop();
    double val1 = stack.pop().toDouble();

    if (sign == "+") {
        stack.push(QString::number(val1 + val2));
    } else if (sign == "-") {
        stack.push(QString::number(val1 - val2));
    } else if (sign == "*") {
        stack.push(QString::number(val1 * val2));
    } else if (sign == "/") {
        if (val2 == 0) {
            stack.push(QString::number(val1));
            stack.push(sign);
            ui->lineEdit->clear();
            ui->lineEdit_2->setText(stack.toList().join(""));
            return;
        }
        stack.push(QString::number(val1 / val2));
    }

    ui->lineEdit->setText(stack.pop());
    ui->lineEdit_2->setText(stack.toList().join(""));
}

void MainWindow::on_pushButton_sin_clicked()
{
    if (ui->lineEdit->text().length() == 0) return;
    double val = ui->lineEdit->text().toDouble();
    double res = sin(val);
    ui->lineEdit->setText(QString::number(res));
}

void MainWindow::on_pushButton_ln_clicked()
{
    if (ui->lineEdit->text().length() == 0) return;
    double val = ui->lineEdit->text().toDouble();
    if (val <= 0) {
        ui->lineEdit->setText("Error");
        return;
    }
    double res = log(val);
    ui->lineEdit->setText(QString::number(res));
}

void MainWindow::on_pushButton_pow_clicked()
{
    if (ui->lineEdit->text().length() == 0) return;

    if (stack.length() < 2) {
        stack.push(ui->lineEdit->text());
        stack.push("^");
        ui->lineEdit->clear();
        ui->lineEdit_2->setText(stack.toList().join(""));
    } else {
        double val2 = ui->lineEdit->text().toDouble();
        QString sign = stack.pop();
        double val1 = stack.pop().toDouble();
        double res = pow(val1, val2);
        ui->lineEdit->setText(QString::number(res));
        ui->lineEdit_2->clear();
    }
}

void MainWindow::on_pushButton_inv_clicked()
{
    if (ui->lineEdit->text().length() == 0) return;
    double val = ui->lineEdit->text().toDouble();
    if (val == 0) {
        ui->lineEdit->setText("Error");
        return;
    }
    double res = 1.0 / val;
    ui->lineEdit->setText(QString::number(res));
}

void MainWindow::on_pushButton_ms_clicked()
{
    if (ui->lineEdit->text().length() == 0) return;
    memory = ui->lineEdit->text().toDouble();
}

void MainWindow::on_pushButton_mr_clicked()
{
    ui->lineEdit->setText(QString::number(memory));
}

void MainWindow::on_pushButton_mc_clicked()
{
    memory = 0.0;
}

void MainWindow::on_pushButton_mplus_clicked()
{
    if (ui->lineEdit->text().length() == 0) return;
    memory += ui->lineEdit->text().toDouble();
}

void MainWindow::on_pushButton_mminus_clicked()
{
    if (ui->lineEdit->text().length() == 0) return;
    memory -= ui->lineEdit->text().toDouble();
}