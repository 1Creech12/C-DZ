#include "orderwindow.h"
#include <QVBoxLayout>

OrderWindow::OrderWindow(const QString &description, const QString &price, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Заказ");
    setFixedSize(400, 200);

    QLabel *descLabel = new QLabel("Товар:\n" + description);
    descLabel->setWordWrap(true);

    QLabel *priceLabel = new QLabel(price);

    confirmButton = new QPushButton("Оформить заказ");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(descLabel);
    layout->addWidget(priceLabel);
    layout->addWidget(confirmButton);

    connect(confirmButton, &QPushButton::clicked, this, &OrderWindow::confirmOrder);
}

void OrderWindow::confirmOrder()
{
    this->close();
}