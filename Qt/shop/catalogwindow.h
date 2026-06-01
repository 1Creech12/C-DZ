#ifndef CATALOGWINDOW_H
#define CATALOGWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

class CatalogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CatalogWindow(QWidget *parent = nullptr);

private slots:
    void orderProduct();

private:
    QLabel *descriptionLabel;
    QLabel *priceLabel;
    QPushButton *orderButton;
};

#endif // CATALOGWINDOW_H