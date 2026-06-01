#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class OrderWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OrderWindow(const QString &description, const QString &price, QWidget *parent = nullptr);

private slots:
    void confirmOrder();

private:
    QPushButton *confirmButton;
};

#endif // ORDERWINDOW_H